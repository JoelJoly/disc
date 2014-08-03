#include "disc/graphics/VertexAttribFormat.h"

#include "disc/graphics/GraphicsContext.h"

#include <GL/glew.h>

#include <stdexcept>
#include <string>

using namespace disc;
using namespace disc::graphics;

VertexAttribFormat::VertexAttribFormat()
	: format_(GL_BYTE)
	, nbElements_(0)
{
}

VertexAttribFormat::VertexAttribFormat(int32_t format, std::size_t nbElements)
	: format_(format)
	, nbElements_(nbElements)
{
}

VertexAttribFormat::~VertexAttribFormat()
{
}

std::uint8_t VertexAttribFormat::getElementSize() const
{
	switch (format_)
	{
	case GL_UNSIGNED_BYTE:
		return sizeof(GLubyte);
	case GL_UNSIGNED_SHORT:
		return sizeof(GLushort);
	case GL_UNSIGNED_INT:
		return sizeof(GLuint);
	case GL_FLOAT:
		return sizeof(GLfloat);
	default:
		throw std::runtime_error("Unknown vertex attrib format: " + std::to_string(format_));
	}
}

std::size_t VertexAttribFormat::getNbElements() const
{
	return nbElements_;
}

int32_t VertexAttribFormat::getFormat() const
{
	return format_;
}

template <>
int32_t VertexAttribFormat::getAttributeFormat<uint8_t>()
{
	static_assert(sizeof(uint8_t) == sizeof(GLubyte), "uint8_t and GLubyte sizes do not match");
	return GL_UNSIGNED_BYTE;
}

template <>
int32_t VertexAttribFormat::getAttributeFormat<uint16_t>()
{
	static_assert(sizeof(uint16_t) == sizeof(GLushort), "uint16_t and GLushort sizes do not match");
	return GL_UNSIGNED_SHORT;
}

template <>
int32_t VertexAttribFormat::getAttributeFormat<uint32_t>()
{
	static_assert(sizeof(uint32_t) == sizeof(GLuint), "uint32_t and GLuint sizes do not match");
	return GL_UNSIGNED_INT;
}

template <>
int32_t VertexAttribFormat::getAttributeFormat<float>()
{
	static_assert(sizeof(float) == sizeof(GLfloat), "float and GLfloat sizes do not match");
	return GL_FLOAT;
}
