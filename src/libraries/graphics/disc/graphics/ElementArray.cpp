#include "disc/graphics/ElementArray.h"

#include "disc/graphics/VertexAttribFormat.h"

#include <GL/glew.h>

#include <stdexcept>
#include <string>

using namespace disc;
using namespace disc::graphics;

struct ElementArray::PImpl
{
	PImpl()
	{
	}
	~PImpl()
	{
	}
};

ElementArray::ElementArray(GraphicsContext& context)
	: BufferObject(context, BufferObject::indexArray)
{
}

ElementArray::~ElementArray()
{
}

std::size_t ElementArray::getSize() const
{
	return getFormat().getNbElements();
}

int ElementArray::getType() const
{
	return getFormat().getFormat();
}
