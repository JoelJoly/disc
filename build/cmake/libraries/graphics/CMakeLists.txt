set (DISC_LIBRARY_GRAPHICS_SRC_DIR ${DISC_LIBRARY_SRC_DIR}/graphics/disc/graphics)
set (GRAPHICS_SRC
	${DISC_LIBRARY_GRAPHICS_SRC_DIR}/BufferObject.h
	${DISC_LIBRARY_GRAPHICS_SRC_DIR}/BufferObject.cpp
	${DISC_LIBRARY_GRAPHICS_SRC_DIR}/DeviceContext.h
	${DISC_LIBRARY_GRAPHICS_SRC_DIR}/DeviceContext.cpp
	${DISC_LIBRARY_GRAPHICS_SRC_DIR}/DeviceContextImpl.h
	${DISC_LIBRARY_GRAPHICS_SRC_DIR}/ElementArray.h
	${DISC_LIBRARY_GRAPHICS_SRC_DIR}/ElementArray.inl
	${DISC_LIBRARY_GRAPHICS_SRC_DIR}/ElementArray.cpp
	${DISC_LIBRARY_GRAPHICS_SRC_DIR}/GraphicsContext.h
	${DISC_LIBRARY_GRAPHICS_SRC_DIR}/GraphicsContext.cpp
	${DISC_LIBRARY_GRAPHICS_SRC_DIR}/Quadrilaterals.h
	${DISC_LIBRARY_GRAPHICS_SRC_DIR}/Quadrilaterals.cpp
	${DISC_LIBRARY_GRAPHICS_SRC_DIR}/Rectangular.h
	${DISC_LIBRARY_GRAPHICS_SRC_DIR}/Rectangular.cpp
	${DISC_LIBRARY_GRAPHICS_SRC_DIR}/Surface.h
	${DISC_LIBRARY_GRAPHICS_SRC_DIR}/Surface.cpp
	${DISC_LIBRARY_GRAPHICS_SRC_DIR}/VertexArrayObject.h
	${DISC_LIBRARY_GRAPHICS_SRC_DIR}/VertexArrayObject.cpp
	${DISC_LIBRARY_GRAPHICS_SRC_DIR}/VertexAttribArray.h
	${DISC_LIBRARY_GRAPHICS_SRC_DIR}/VertexAttribArray.inl
	${DISC_LIBRARY_GRAPHICS_SRC_DIR}/VertexAttribArray.cpp
	${DISC_LIBRARY_GRAPHICS_SRC_DIR}/VertexAttribFormat.h
	${DISC_LIBRARY_GRAPHICS_SRC_DIR}/VertexAttribFormat.cpp
	${DISC_LIBRARY_GRAPHICS_SRC_DIR}/Window.h
	${DISC_LIBRARY_GRAPHICS_SRC_DIR}/Window.cpp
	)

include_directories(${DISC_LIBRARY_SRC_DIR}/graphics)
include_directories(${GLEW_INCLUDE_PATH})

add_library(graphics ${GRAPHICS_SRC})
add_definitions(-DGLEW_STATIC)
target_link_libraries(graphics ${GLEW_STATIC_LIBRARY} OpenGL32)
