cmake_minimum_required(VERSION 3.10)

project(Streamer VERSION 1.0)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(CMAKE_BUILD_TYPE MATCHES "Debug")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
endif()

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(${SOURCE_DIR})
add_subdirectory(${INCLUDE_DIR})

add_executable(streamer ${SOURCE_DIR}/main.cpp)

include_directories(${GSTREAMER_INCLUDE_DIRS})
include_directories(${INCLUDE_DIR})

target_link_libraries(streamer STREAMER_LIB)

target_include_directories(streamer PUBLIC ${INCLUDE_DIR})