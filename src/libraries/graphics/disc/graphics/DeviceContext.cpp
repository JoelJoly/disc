#include "disc/graphics/DeviceContext.h"

#include "disc/graphics/Window.h"

#include <GL/glew.h>
#include <GL/wglew.h>
#include "disc/graphics/DeviceContextImpl.h"

using namespace disc;
using namespace disc::graphics;

DeviceContext::DeviceContext(Window& window)
	: pImpl_(new PImpl())
{
	pImpl_->hwnd_ = static_cast<HWND>(window.getHandle());
	pImpl_->hdc_ = GetDC(pImpl_->hwnd_);
}

DeviceContext::~DeviceContext()
{
	// eelease the device context from our window
	ReleaseDC(pImpl_->hwnd_, pImpl_->hdc_);
}
