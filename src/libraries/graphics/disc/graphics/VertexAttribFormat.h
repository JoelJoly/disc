#ifndef DISC_GRAPHICS_VERTEXATTRIBFORMAT_H
#define DISC_GRAPHICS_VERTEXATTRIBFORMAT_H

#include <cstdint>
#include <memory>

namespace disc
{
	namespace graphics
	{
		class VertexAttribFormat
		{
		public:
			VertexAttribFormat();
			VertexAttribFormat(int32_t format, std::size_t nbElements);
			~VertexAttribFormat();

			std::uint8_t getElementSize() const;
			std::size_t getNbElements() const;
			int32_t getFormat() const;

			template <typename T>
			static int32_t getAttributeFormat();
		private:
			int32_t format_;
			std::size_t nbElements_;
		};
	}
}

#endif
