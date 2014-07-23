#ifndef DISC_GRAPHICS_DEVICECONTEXTIMPL_H
#define DISC_GRAPHICS_DEVICECONTEXTIMPL_H

namespace disc
{
	namespace graphics
	{
		// this struct is meant to be an implementation detail shared across a few classes
		// so there is no include of the necessary files in this header
		// it has to be done by the cpp file before including this file
		struct DeviceContext::PImpl
		{
			HWND hwnd_;
			HDC hdc_;
		};
	}
}

#endif
