#include "disc/graphics/VertexAttribFormat.h"

namespace disc
{
	namespace graphics
	{
		template <typename T>
		typename std::enable_if<VertexAttribArray::ValidPointer<T>::value>::type VertexAttribArray::setData(const T* data, std::size_t dataSize)
		{
			bind();
			setDataAndFormat(data, VertexAttribFormat(VertexAttribFormat::getAttributeFormat<T>(), dataSize));
		}
	}
}
