set (DISC_APPLICATION_MINIMAL_SRC_DIR ${DISC_APPLICATION_SRC_DIR}/minimal/disc)
set (MNIMAL_SRC
	${DISC_APPLICATION_MINIMAL_SRC_DIR}/minimal.cpp
	)

include_directories(${DISC_LIBRARY_SRC_DIR}/graphics)

add_executable(minimal ${MNIMAL_SRC})
target_link_libraries(minimal graphics)
