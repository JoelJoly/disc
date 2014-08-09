#ifndef DISC_GRAPHICS_GRAPHICSCONTEXT_H
#define DISC_GRAPHICS_GRAPHICSCONTEXT_H

#include <memory>
#include <string>

namespace disc
{
	namespace graphics
	{
		class DeviceContext;
		class Pipeline;

		class GraphicsContext
		{
		public:
			explicit GraphicsContext(const DeviceContext& deviceContext);
			~GraphicsContext();

			void resize(unsigned int width, unsigned int height);
			void render(); // should be in a camera class

			std::shared_ptr<Pipeline> addPipeline();

			void checkError(const std::string& file, uint32_t line) const;

		private:
			struct PImpl;
			std::unique_ptr<PImpl> pImpl_;
		};
	}
}

#endif
