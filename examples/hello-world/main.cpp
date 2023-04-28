#include <iostream>

#include "GLFW/glfw3.h"
#include "pesto.hpp"

#include "shaders/sprite/sprite.fs.hpp"
#include "shaders/sprite/sprite.vs.hpp"

int main()
{
    Application app = {};
	
    app.loader.generatedDirectory = "examples/generated/";

    app.renderer.shader = app.loader.loadProgram("cubes");

    app.run();

    return 0;
}

void Application::update()
{
    // check if escape is pressed
    if (input.keyPressed(GLFW_KEY_ESCAPE))
    {
        this->close();
    }
}

void Application::tick()
{
}

void Application::draw()
{
}
