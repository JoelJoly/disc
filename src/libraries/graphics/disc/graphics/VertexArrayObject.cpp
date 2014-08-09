#include "disc/graphics/VertexArrayObject.h"

#include "disc/graphics/ElementArray.h"
#include "disc/graphics/VertexAttribArray.h"

#include "disc/graphics/utils/Error.h"

#include <GL/glew.h>

#include <deque>
#include <stdexcept>
#include <string>

using namespace disc;
using namespace disc::graphics;

struct VertexArrayObject::PImpl
{
	PImpl(GraphicsContext& context)
		: context_(context)
	{
		glGenVertexArrays(1, &array_);
	}
	~PImpl()
	{
		glDeleteVertexArrays(1, &array_);
	}
	GraphicsContext& context_;
	GLuint array_;
	std::deque<VertexAttribArray> attribs_;
	std::unique_ptr<ElementArray> elements_;
};

VertexArrayObject::VertexArrayObject(GraphicsContext& context)
	: pImpl_(new PImpl(context))
{
}

VertexArrayObject::~VertexArrayObject()
{
}

void VertexArrayObject::bind() const
{
	glBindVertexArray(pImpl_->array_);
	GRAPHICS_CHECK_ERROR(pImpl_->context_);
}

VertexAttribArray& VertexArrayObject::addVertexAttrib()
{
	pImpl_->attribs_.emplace_back(pImpl_->context_);
	return pImpl_->attribs_.back();
}

ElementArray& VertexArrayObject::getElementArray()
{
	if (! pImpl_->elements_)
		pImpl_->elements_.reset(new ElementArray(pImpl_->context_));
	return *pImpl_->elements_;
}

void VertexArrayObject::compile()
{
	bind();
	for (auto& attrib : pImpl_->attribs_)
	{
		attrib.bindPointer(0);
	}
}

void VertexArrayObject::render() const
{
	if (! pImpl_->elements_)
		throw std::runtime_error("VAO has no element array");
	bind();
	pImpl_->elements_->bind();
	glDrawElements(GL_TRIANGLES, pImpl_->elements_->getSize(), static_cast<GLenum>(pImpl_->elements_->getType()), nullptr);
	GRAPHICS_CHECK_ERROR(pImpl_->context_);
}
