#include "disc/graphics/VertexAttribArray.h"

#include "disc/graphics/GraphicsContext.h"

#include "disc/graphics/utils/Error.h"

#include <GL/glew.h>

#include <stdexcept>
#include <string>

using namespace disc;
using namespace disc::graphics;

struct VertexAttribArray::PImpl
{
	PImpl()
	{
	}
	~PImpl()
	{
	}
};

VertexAttribArray::VertexAttribArray(GraphicsContext& context)
	: BufferObject(context, BufferObject::vertexArray)
	, pImpl_(new PImpl())
{
}

VertexAttribArray::~VertexAttribArray()
{
}

void VertexAttribArray::bindPointer(uint32_t location) const
{
	BufferObject::bind();
	glEnableVertexAttribArray(static_cast<GLuint>(location));
	GRAPHICS_CHECK_ERROR(getContext());
	GLint bufferBinding;
	glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &bufferBinding);
	GRAPHICS_CHECK_ERROR(getContext());
	glVertexAttribPointer(static_cast<GLuint>(location), 4, GL_FLOAT, GL_FALSE, 0, 0);
	GRAPHICS_CHECK_ERROR(getContext());

}
