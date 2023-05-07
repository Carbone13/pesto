cmake_minimum_required(VERSION 3.23)
include(cmake/AssetCompiler.cmake)
set(CMAKE_CXX_STANDARD 17)
project(pesto)

# add dependencies
add_subdirectory(lib)
include_directories(include/pesto src/)

# compile pesto
add_library(pesto STATIC
        # Headers
        include/pesto/pesto.hpp
        include/pesto/loader.hpp
        src/camera/camera.hpp
        src/gfx/renderer.hpp
        src/gfx/sprite.hpp
        src/gfx/texture.hpp
        src/input/input.hpp
        src/object/object.hpp
        src/window/window.hpp
        src/time.hpp
        src/server.hpp
        src/initializer.hpp
        # Sources
        src/camera/camera.cpp
        src/gfx/renderer.cpp
        src/input/input.cpp
        src/object/object.cpp
        src/window/window.cpp
        src/loader.cpp)

target_link_libraries(pesto PUBLIC bgfx bx bimg bimg_decode glfw glm)

target_include_directories(pesto PUBLIC include)
target_include_directories(pesto PRIVATE src)

add_subdirectory(test)