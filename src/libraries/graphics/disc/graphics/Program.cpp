#include "disc/graphics/Program.h"

#include "disc/graphics/GraphicsContext.h"
#include "disc/graphics/VertexAttribFormat.h"

#include "disc/graphics/utils/Error.h"

#include <GL/glew.h>

#include <cmath>

using namespace disc;
using namespace disc::graphics;

struct Program::PImpl
{
	PImpl(GraphicsContext& context)
		: context_(context)
		, vertexShader_(0)
		, fragmentShader_(0)
	{
	}
	void createDefaultProgram()
	{
		context_.bind();
		vertexShader_ = glCreateShader(GL_VERTEX_SHADER);
		GRAPHICS_CHECK_ERROR(context_);
		fragmentShader_ = glCreateShader(GL_FRAGMENT_SHADER);
		GRAPHICS_CHECK_ERROR(context_);
		{
			const GLchar vertexSource[] =
				"#version 430 core\n"
				"uniform mat4 projectionMatrix;\n"
				"layout(location = 0) in vec4 in_position;\n"
				"void main()\n"
				"{\n"
				"	gl_Position = in_position * projectionMatrix;\n"
				"}";
			const GLchar* sourcePointer = &vertexSource[0];
			glShaderSource(vertexShader_, 1, &sourcePointer, nullptr);
			GRAPHICS_CHECK_ERROR(context_);
			glCompileShader(vertexShader_);
			GRAPHICS_CHECK_ERROR(context_);
			checkCompile(vertexShader_);
		}
		{
			const GLchar fragmentSource[] =
				"#version 430 core\n"
				"layout(location = 0) out vec4 out_color;\n"
				"void main()\n"
				"{\n"
				"	out_color = vec4(.0, 0.4, 0.4, 1.);\n"
				"}";
			const GLchar* sourcePointer = &fragmentSource[0];
			glShaderSource(fragmentShader_, 1, &sourcePointer, nullptr);
			GRAPHICS_CHECK_ERROR(context_);
			glCompileShader(fragmentShader_);
			GRAPHICS_CHECK_ERROR(context_);
			checkCompile(fragmentShader_);
		}
		program_ = glCreateProgram();
		GRAPHICS_CHECK_ERROR(context_);
		glAttachShader(program_, vertexShader_);
		GRAPHICS_CHECK_ERROR(context_);
		glAttachShader(program_, fragmentShader_);
		GRAPHICS_CHECK_ERROR(context_);
		glLinkProgram(program_);
		GRAPHICS_CHECK_ERROR(context_);
		checkLink(program_);
		// bind a constant projection matrix
		glUseProgram(program_);
		GRAPHICS_CHECK_ERROR(context_);
		GLfloat fov(90.f);
		static const GLfloat pi = 4*atan(1.f);
		GLfloat near(0.1f), far(200.f), scale(1.f / tan(pi/180*(fov * 0.5f)));
		GLfloat projectionMatrix[16] = {
			scale, 0, 0, 0,
			0, scale, 0, 0,
			0, 0, -(far + near) / (far - near), -2 * (far * near) / (far - near),
			0, 0, -1, 0
		};
		glUniformMatrix4fv(0, 1, false, projectionMatrix);
		GRAPHICS_CHECK_ERROR(context_);
	}
	void checkCompile(GLuint shader)
	{
		GLint compiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		GRAPHICS_CHECK_ERROR(context_);
		if (! compiled)
		{
			GLint logLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
			GRAPHICS_CHECK_ERROR(context_);
			const uint16_t staticBufferSize = 256;
			GLchar staticBuffer[staticBufferSize];
			std::unique_ptr<GLchar> dynamicbuffer;
			GLchar* infoLog = &staticBuffer[0];
			if (logLength > staticBufferSize)
			{
				dynamicbuffer.reset(new GLchar[logLength]);
				infoLog = dynamicbuffer.get();
			}
			GLsizei length;
			glGetShaderInfoLog(shader, logLength, &length, infoLog);
			GRAPHICS_CHECK_ERROR(context_);
			throw std::runtime_error(std::string("Error while loading shader: ") + infoLog);
		}
	}
	void checkLink(GLuint program)
	{
		GLint linked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &linked);
		GRAPHICS_CHECK_ERROR(context_);
		if (! linked)
		{
			GLint logLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
			GRAPHICS_CHECK_ERROR(context_);
			const uint16_t staticBufferSize = 256;
			GLchar staticBuffer[staticBufferSize];
			std::unique_ptr<GLchar> dynamicbuffer;
			GLchar* infoLog = &staticBuffer[0];
			if (logLength > staticBufferSize)
			{
				dynamicbuffer.reset(new GLchar[logLength]);
				infoLog = dynamicbuffer.get();
			}
			GLsizei length;
			glGetProgramInfoLog(program, logLength, &length, infoLog);
			GRAPHICS_CHECK_ERROR(context_);
			throw std::runtime_error(std::string("Error while loading shader: ") + infoLog);
		}
	}
	GraphicsContext& context_;
	GLuint vertexShader_;
	GLuint fragmentShader_;
	GLuint program_;
};


Program::Program(GraphicsContext& context)
	: pImpl_(new PImpl(context))
{
	pImpl_->createDefaultProgram();
}

Program::~Program()
{
}

void Program::bind()
{
	pImpl_->context_.bind();
	glUseProgram(pImpl_->program_);
	GRAPHICS_CHECK_ERROR(pImpl_->context_);
}
