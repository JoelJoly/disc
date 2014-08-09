#ifndef DISC_GRAPHICS_WINDOW_H
#define DISC_GRAPHICS_WINDOW_H

#include <memory>

namespace disc
{
	namespace graphics
	{
		class GraphicsContext;

		class Window
		{
		public:
			struct Dimensions
			{
				uint32_t top;
				uint32_t left;
				uint32_t height;
				uint32_t width;
			};
		public:
			Window();
			~Window();

			void show();
			Dimensions getDimensions() const;

			bool aboutToClose() const;
			void processMessages();
			void render();

			void* getHandle() const;

			GraphicsContext& getGraphicsContext();

		private:
			std::unique_ptr<GraphicsContext> createGraphicsContext();
			struct PImpl;
			std::unique_ptr<PImpl> pImpl_;
		};
	}
}

#endif
