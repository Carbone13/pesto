#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "GLFW/glfw3.h"
#include "../server.hpp"

namespace pesto
{
    class WindowHandle : Server
    {
        void createWindow(int sizeX, int sizeY);

      public:
        WindowHandle(Application *app, int sizeX, int sizeY);

        GLFWwindow *window{nullptr};
    };
}

#endif // !WINDOW_HPP
