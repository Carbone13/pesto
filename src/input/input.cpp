#include "pesto.hpp"

namespace pesto
{
    Input::Input(Application *app) : Server(app)
    {
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
}