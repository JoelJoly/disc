#ifndef DISC_GRAPHICS_GRAPHICSCONTEXT_H
#define DISC_GRAPHICS_GRAPHICSCONTEXT_H

#include <memory>

namespace disc
{
	namespace graphics
	{
		class DeviceContext;

		class GraphicsContext
		{
		public:
			explicit GraphicsContext(const DeviceContext& deviceContext);
			~GraphicsContext();

			void resize(unsigned int width, unsigned int height);
			void render(); // should be in a camera class

		private:
			struct PImpl;
			std::unique_ptr<PImpl> pImpl_;
		};
	}
}

#endif
