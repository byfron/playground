cmake_minimum_required(VERSION 3.12)

project(playground)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")

set_directory_properties(PROPERTIES COMPILE_DEFINITIONS_DEBUG "_DEBUG")

include_directories(src)
include_directories(third-party/)
include_directories(third-party/imgui/gl3w)

add_subdirectory(third-party)
add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(examples)