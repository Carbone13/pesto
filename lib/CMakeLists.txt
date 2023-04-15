set(BGFX_BUILD_EXAMPLES OFF)

add_subdirectory(bgfx.cmake)
add_subdirectory(glfw)
add_subdirectory(glm)

target_include_directories(${PROJECT_NAME} PUBLIC glfw/include glm)
target_link_libraries(${PROJECT_NAME} PUBLIC bgfx bx bimg_decode bimg glfw)
