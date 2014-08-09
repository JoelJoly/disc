#ifndef DISC_GRAPHICS_BUFFEROBJECT_H
#define DISC_GRAPHICS_BUFFEROBJECT_H

#include <memory>

namespace disc
{
	namespace graphics
	{
		class GraphicsContext;
		class VertexAttribFormat;

		class BufferObject
		{
		public:
			enum Type
			{
				vertexArray,
				indexArray,
			};
		public:
			BufferObject(GraphicsContext& context, uint32_t type);
			virtual ~BufferObject();

			void bind() const;
		protected:
			void setDataAndFormat(const void* data, const VertexAttribFormat& format);
			const VertexAttribFormat& getFormat() const;

			GraphicsContext& getContext();
			const GraphicsContext& getContext() const;

		private:
			BufferObject(const BufferObject&);
			BufferObject& operator=(const BufferObject&);

		private:
			struct PImpl;
			std::unique_ptr<PImpl> pImpl_;
		};
	}
}

#endif
