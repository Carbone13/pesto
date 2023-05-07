#include "pesto.hpp"

#include <iostream>

namespace pesto
{
    WindowHandle::WindowHandle(Application *app, Initializer initializer) : Server(app)
    {
        if (glfwInit() == GLFW_FALSE)
        {
            std::cerr << "[ERROR] Could not initialize GLFW" << std::endl;
        }

        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        window = glfwCreateWindow(initializer.windowWidth, initializer.windowHeight, initializer.windowName, nullptr, nullptr);

        if (!window)
        {
            std::cerr << "[ERROR] Could not initialize GLFW Window" << std::endl;
        }
    }
}