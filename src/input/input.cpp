#include "input/input.hpp"
#include "pesto.hpp"

Input::Input(Application *mainApp)
{
    app = mainApp;
}

bool Input::keyPressed(int key)
{
    return glfwGetKey(app->windowHandle.window, key) == GLFW_PRESS;
}

int Input::getAxis(int keyA, int keyB)
{
    int v{0};

    if (keyPressed(keyA))
        v++;
    if (keyPressed(keyB))
        v--;

    return v;
}
