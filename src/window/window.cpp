#include "window.hpp"
#include "pesto.hpp"

#include <iostream>

namespace pesto
{
    WindowHandle::WindowHandle(Application *mainApp, int sizeX, int sizeY)
    {
        app = mainApp;
        createWindow(sizeX, sizeY);
    }

    void WindowHandle::createWindow(int sizeX, int sizeY)
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

        window = glfwCreateWindow(sizeX, sizeY, "Pesto Application", nullptr, nullptr);

        if (!window)
        {
            std::cerr << "[ERROR] Could not initialize GLFW Window" << std::endl;
        }
    }

    void WindowHandle::poll()
    {
        glfwPollEvents();
    }
}