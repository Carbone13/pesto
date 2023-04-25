cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)

project(pesto)

add_subdirectory(lib)

include_directories(lib/bgfx.cmake/bgfx/include lib/bgfx.cmake/bx/include lib/bgfx.cmake/bimg/include)
include_directories(lib/glfw/include lib/glm)

# PESTO
file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS src/*.hpp src/*.h)

add_library(pesto STATIC ${SOURCES} ${HEADERS})
target_link_libraries(pesto PUBLIC bgfx bx bimg bimg_decode glfw glm)
target_include_directories(pesto PUBLIC src)

# EXAMPLES | TESTS
option(EXAMPLES "Build examples." ON)

if (EXAMPLES)
	add_subdirectory(examples)
endif(EXAMPLES)
