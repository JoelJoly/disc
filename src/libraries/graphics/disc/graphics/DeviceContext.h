#ifndef DISC_GRAPHICS_DEVICECONTEXT_H
#define DISC_GRAPHICS_DEVICECONTEXT_H

#include <memory>

namespace disc
{
	namespace graphics
	{
		class Window;

		class DeviceContext
		{
		public:
			explicit DeviceContext(Window& window);
			~DeviceContext();
			struct PImpl;
		private:
			std::unique_ptr<PImpl> pImpl_;
		private:
			friend class DeviceContextAttorney;
		};

		class DeviceContextAttorney
		{
		public:
			friend class GraphicsContext;
			static DeviceContext::PImpl& getPImpl(const DeviceContext& deviceContext)
			{
				return *deviceContext.pImpl_;
			}
		};
	}
}

#endif
