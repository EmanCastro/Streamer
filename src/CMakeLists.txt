file(GLOB SOURCES "*.c")

add_library(STREAMER_LIB ${SOURCES})
target_link_libraries(STREAMER_LIB ${GSTREAMER_LIBRARIES})
target_include_directories(STREAMER_LIB PRIVATE ${GSTREAMER_INCLUDE_DIRS})
target_include_directories(STREAMER_LIB PRIVATE ${INCLUDE_DIR})