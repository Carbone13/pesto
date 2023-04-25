#include <iostream>

#include "GLFW/glfw3.h"
#include "pesto.hpp"

int main()
{
    Application app = {};

    return 0;
}

void Application::update ()
{
    // check if escape is pressed
    if (input.keyPressed(GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(windowHandle.window, 1); // exit
    }
}

void Application::tick() {

}

void Application::draw() {

}
