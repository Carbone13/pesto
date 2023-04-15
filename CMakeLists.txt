cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 20)

project(pesto)

# Sources
file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS src/*.hpp src/*.h)


# Executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC src/)

# Libraries Linking
add_subdirectory(lib)
