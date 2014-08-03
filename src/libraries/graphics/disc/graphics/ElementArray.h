#ifndef DISC_GRAPHICS_ELEMENTARRAY_H
#define DISC_GRAPHICS_ELEMENTARRAY_H

#include "disc\graphics\BufferObject.h"

#include <memory>
#include <type_traits>

namespace disc
{
	namespace graphics
	{
		class ElementArray : public BufferObject
		{
		public:
			template <typename T>
			struct ValidPointer : public std::integral_constant<bool,
				std::is_unsigned<T>::value && std::is_integral<T>::value>
			{};
		public:
			explicit ElementArray(GraphicsContext& context);
			virtual ~ElementArray();

			template <typename T>
			typename std::enable_if<ValidPointer<T>::value>::type setData(const T* data, std::size_t dataSize);

			std::size_t getSize() const;
			int getType() const;

		private:
			struct PImpl;
			std::unique_ptr<PImpl> pImpl_;
		};
	}
}

#include "ElementArray.inl"

#endif
