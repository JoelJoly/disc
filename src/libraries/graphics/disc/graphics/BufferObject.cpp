#include "disc/graphics/BufferObject.h"

#include "disc/graphics/VertexAttribFormat.h"

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
	}
	~PImpl()
	{
		glDeleteBuffers(1, &buffer_);
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
}

void BufferObject::setDataAndFormat(const void* data, const VertexAttribFormat& format)
{
	pImpl_->format_ = format;
	glBufferData(pImpl_->bindTarget_, format.getElementSize() * format.getNbElements(), data, GL_STATIC_DRAW);
}

const VertexAttribFormat& BufferObject::getFormat() const
{
	return pImpl_->format_;
}
