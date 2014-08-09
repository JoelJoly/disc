#ifndef DISC_GRAPHICS_UTILS_ERROR_H
#define DISC_GRAPHICS_UTILS_ERROR_H

#include <cstdint>

#define GRAPHICS_CHECK_ERROR(gc) ::disc::graphics::utils::checkError(gc, __FILE__, __LINE__)

namespace disc
{
	namespace graphics
	{
		class GraphicsContext;

		namespace utils
		{
			void checkError(const GraphicsContext& gc);
			void checkError(const GraphicsContext& gc, const char* file, uint32_t line);
		}
	}
}

#endif
