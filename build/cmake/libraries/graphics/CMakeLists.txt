set (DISC_LIBRARY_GRAPHICS_SRC_DIR ${DISC_LIBRARY_SRC_DIR}/graphics/disc/graphics)
set (GRAPHICS_SRC
	${DISC_LIBRARY_GRAPHICS_SRC_DIR}/DeviceContext.h
	${DISC_LIBRARY_GRAPHICS_SRC_DIR}/DeviceContext.cpp
	${DISC_LIBRARY_GRAPHICS_SRC_DIR}/DeviceContextImpl.h
	${DISC_LIBRARY_GRAPHICS_SRC_DIR}/GraphicsContext.h
	${DISC_LIBRARY_GRAPHICS_SRC_DIR}/GraphicsContext.cpp
	${DISC_LIBRARY_GRAPHICS_SRC_DIR}/Window.h
	${DISC_LIBRARY_GRAPHICS_SRC_DIR}/Window.cpp
	)

include_directories(${DISC_LIBRARY_SRC_DIR}/graphics)
include_directories(${GLEW_INCLUDE_PATH})

add_library(graphics ${GRAPHICS_SRC})
add_definitions(-DGLEW_STATIC)
target_link_libraries(graphics ${GLEW_STATIC_LIBRARY} OpenGL32)
