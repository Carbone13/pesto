cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

project(pesto)

add_subdirectory(lib)

# PESTO
file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS src/*.hpp src/*.h)

add_library(pesto STATIC ${SOURCES} ${HEADERS})

target_link_libraries(pesto PUBLIC bgfx bx bimg bimg_decode glfw glm)
target_include_directories(pesto PUBLIC src)