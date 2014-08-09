#include "disc/graphics/BufferObject.h"

#include "disc/graphics/VertexAttribFormat.h"

#include "disc/graphics/utils/Error.h"

#include <GL/glew.h>

#include <stdexcept>
#include <string>

using namespace disc;
using namespace disc::graphics;

namespace
{
	GLenum targetFromType(uint32_t type)
	{
		switch (type)
		{
		case BufferObject::vertexArray:
			return GL_ARRAY_BUFFER;
		case BufferObject::indexArray:
			return GL_ELEMENT_ARRAY_BUFFER;
		default:
			throw std::runtime_error("Unsupported buffer type: " + std::to_string(type));
		}
	}
}

struct BufferObject::PImpl
{
	PImpl(GraphicsContext& context, uint32_t type)
		: context_(context)
		, bindTarget_(targetFromType(type))
	{
		glGenBuffers(1, &buffer_);
		GRAPHICS_CHECK_ERROR(context_);
	}
	~PImpl()
	{
		glDeleteBuffers(1, &buffer_);
		GRAPHICS_CHECK_ERROR(context_);
	}
	GraphicsContext& context_;
	GLuint buffer_;
	GLenum bindTarget_;
	VertexAttribFormat format_;
};

BufferObject::BufferObject(GraphicsContext& context, uint32_t type)
	: pImpl_(new PImpl(context, type))
{
}

BufferObject::~BufferObject()
{
}

void BufferObject::bind() const
{
	glBindBuffer(pImpl_->bindTarget_, pImpl_->buffer_);
	GRAPHICS_CHECK_ERROR(pImpl_->context_);
}

void BufferObject::setDataAndFormat(const void* data, const VertexAttribFormat& format)
{
	pImpl_->format_ = format;
	glBufferData(pImpl_->bindTarget_, format.getElementSize() * format.getNbElements(), data, GL_STATIC_DRAW);
	GRAPHICS_CHECK_ERROR(pImpl_->context_);
}

const VertexAttribFormat& BufferObject::getFormat() const
{
	return pImpl_->format_;
}

GraphicsContext& BufferObject::getContext()
{
	return pImpl_->context_;
}

const GraphicsContext& BufferObject::getContext() const
{
	return pImpl_->context_;
}
