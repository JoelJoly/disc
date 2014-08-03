#ifndef DISC_GRAPHICS_VERTEXARRAYOBJECT_H
#define DISC_GRAPHICS_VERTEXARRAYOBJECT_H

#include <memory>

namespace disc
{
	namespace graphics
	{
		class ElementArray;
		class GraphicsContext;
		class VertexAttribArray;

		class VertexArrayObject
		{
		public:
			explicit VertexArrayObject(GraphicsContext& context);
			virtual ~VertexArrayObject();

			void bind() const;
			VertexAttribArray& addVertexAttrib();
			ElementArray& getElementArray();

			void compile();
			void render() const;

		private:
			struct PImpl;
			std::unique_ptr<PImpl> pImpl_;
		};
	}
}

#endif
