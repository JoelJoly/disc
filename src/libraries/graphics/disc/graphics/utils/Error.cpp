#include "disc/graphics/utils/Error.h"

#include "disc/graphics/GraphicsContext.h"

using namespace disc;
using namespace disc::graphics;

void utils::checkError(const GraphicsContext& gc)
{
	checkError(gc, NULL, 0);
}

void utils::checkError(const GraphicsContext& gc, const char* file, uint32_t line)
{
	gc.checkError(file ? file : "Unknown file", line);
}
