namespace disc
{
	namespace graphics
	{
		template <typename T>
		typename std::enable_if<ElementArray::ValidPointer<T>::value>::type ElementArray::setData(const T* data, std::size_t dataSize)
		{
			bind();
			setDataAndFormat(data, VertexAttribFormat(VertexAttribFormat::getAttributeFormat<T>(), dataSize));
		}
	}
}
