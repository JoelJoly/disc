#include "disc/graphics/GraphicsContext.h"

#include "disc/graphics/DeviceContext.h"

#include <GL/glew.h>
#include <GL/wglew.h>
#include "disc/graphics/DeviceContextImpl.h"

#include <iostream>
#include <stdexcept>
#include <string>

using namespace disc;
using namespace disc::graphics;

struct GraphicsContext::PImpl
{
	PImpl(HGLRC openGL1Context, HDC hdc)
		: hrc_(openGL1Context)
		, hdc_(hdc)
		, width_()
		, height_()
	{
	}
	PImpl(DeviceContext::PImpl& deviceContextImpl)
		: width_()
		, height_()
	{
		create40Context(deviceContextImpl.hdc_);
	}
	~PImpl()
	{
		wglMakeCurrent(hdc_, 0); // remove current GL context in case it is our own
		wglDeleteContext(hrc_); // delete our rendering context
	}
	void create40Context(HDC hdc)
	{
		if (!hdc)
			throw std::runtime_error("Cannot create a GL context without a HDC");
		hdc_ = hdc;
		PIXELFORMATDESCRIPTOR pfd;
		memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		// we want a openGL context with double buffer to render to a window
		pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;
		pfd.cDepthBits = 32;
		pfd.iLayerType = PFD_MAIN_PLANE;

		// ensure can get the pixel format we asked for
		int pixelFormat = ChoosePixelFormat(hdc, &pfd);
		if (pixelFormat == 0)
			throw std::runtime_error("Could not select a correct pixel format");

		if (! SetPixelFormat(hdc, pixelFormat, &pfd))
			throw std::runtime_error("Could not set the pixel format");

		// Create an OpenGL 2.1 context for our device context, destroyed at the end of the scope
		{
			PImpl tempContext(wglCreateContext(hdc), hdc);
			hrc_ = tempContext.finishCreate40Context();
		}
		makeCurrent();
		// retrieve and store version
		glGetIntegerv(GL_MAJOR_VERSION, &majorVersion_);
		glGetIntegerv(GL_MINOR_VERSION, &minorVersion_);
	}
	HGLRC finishCreate40Context()
	{
		// make sure we have a valid OpenGL context valid
		makeCurrent();
		GLenum error = glewInit();
		if (error != GLEW_OK)
			throw std::runtime_error("GLEW initialization failed");
		// make sure we can create OpenGL 3+ contexts
		if (! wglewIsSupported("WGL_ARB_create_context") == 1)
			throw std::runtime_error("Your graphics card does not support OpenGL 3.x or beyond");
		int minorVersion = 5;
		// loop until maximum supported minor version is found and early exit
		while (minorVersion >= 0)
		{
			int attributes[] =
			{
				WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
				WGL_CONTEXT_MINOR_VERSION_ARB, minorVersion,
				WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
				WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
				0, 0
			};
			// empty last error buffer
			SetLastError(ERROR_SUCCESS);
			HGLRC hrc4x = wglCreateContextAttribsARB(hdc_, NULL, attributes); // Create and OpenGL 4.x context based on the given attributes
			DWORD contextCreationResult = GetLastError();
			if (contextCreationResult == ERROR_SUCCESS)
				return hrc4x;
			if (HRESULT_CODE(contextCreationResult) != ERROR_INVALID_VERSION_ARB)
				throw std::runtime_error("OpenGL 4." + std::to_string(minorVersion) + " context creation failed.");
			--minorVersion;
		}
		throw std::runtime_error("OpenGL 4.x context creation failed");
	}
	void makeCurrent()
	{
		wglMakeCurrent(hdc_, hrc_);
	}
	void checkGLError() const
	{
		GLenum glError = glGetError();
		if (glError != GL_NO_ERROR)
			std::cerr << "GL Error: " << glError << std::endl;
	}
	void releaseCurrent()
	{
		wglMakeCurrent(hdc_, nullptr);
	}

	HGLRC hrc_;
	HDC hdc_;
	int majorVersion_;
	int minorVersion_;
	unsigned int width_;
	unsigned int height_;
};

GraphicsContext::GraphicsContext(const DeviceContext& deviceContext)
	: pImpl_(new PImpl(DeviceContextAttorney::getPImpl(deviceContext)))
{
}

GraphicsContext::~GraphicsContext()
{
}

void GraphicsContext::resize(unsigned int width, unsigned int height)
{
	pImpl_->width_ = width;
	pImpl_->height_ = height;
}

void GraphicsContext::render()
{
	pImpl_->makeCurrent();
	glClearColor(0.6f, 0.7f, 0.3f, 0.f);
	glViewport(0, 0, pImpl_->width_, pImpl_->height_);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	SwapBuffers(pImpl_->hdc_);
	pImpl_->checkGLError();
	pImpl_->releaseCurrent();
}
