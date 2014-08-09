#ifndef DISC_GRAPHICS_RECTANGULAR_H
#define DISC_GRAPHICS_RECTANGULAR_H

#include "disc\graphics\Quadrilaterals.h"

#include <memory>

namespace disc
{
	namespace graphics
	{
		class GraphicsContext;
		class VertexArrayObject;

		class Rectangular : public Quadrilaterals
		{
		public:
			Rectangular(float width, float height, float depth = 0.f);
			virtual ~Rectangular();

			// add an offset on z axis
			void setDepth(float depth);

			std::shared_ptr<VertexArrayObject> generateGeometry(GraphicsContext& graphicsContext) const;

		private:
			struct PImpl;
			std::unique_ptr<PImpl> pImpl_;
		};
	}
}

#endif
