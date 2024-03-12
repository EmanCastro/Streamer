cmake_minimum_required(VERSION 3.10)

project(Streamer VERSION 1.0)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(${SOURCE_DIR})
add_subdirectory(${INCLUDE_DIR})

add_executable(streamer ${SOURCE_DIR}/main.c)

include_directories(${GSTREAMER_INCLUDE_DIRS})
include_directories(${INCLUDE_DIR})

target_link_libraries(streamer STREAMER_LIB)

target_include_directories(streamer PUBLIC ${INCLUDE_DIR})