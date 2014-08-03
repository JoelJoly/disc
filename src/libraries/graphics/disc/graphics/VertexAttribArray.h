#ifndef DISC_GRAPHICS_VERTEXATTRIBARRAY_H
#define DISC_GRAPHICS_VERTEXATTRIBARRAY_H

#include "disc\graphics\BufferObject.h"

#include <memory>
#include <type_traits>

namespace disc
{
	namespace graphics
	{
		class VertexAttribArray : public BufferObject
		{
		public:
			template <typename T>
			struct ValidPointer : std::is_same<T, float> // only floats for now
			{};
		public:
			explicit VertexAttribArray(GraphicsContext& context);
			virtual ~VertexAttribArray();

			// calls bind and assign data to given location
			void bindPointer(uint32_t location) const;

			template <typename T>
			typename std::enable_if<ValidPointer<T>::value>::type setData(const T* data, std::size_t dataSize);
		private:
			struct PImpl;
			std::unique_ptr<PImpl> pImpl_;
		};
	}
}

#include "VertexAttribArray.inl"

#endif
