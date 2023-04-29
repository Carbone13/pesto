#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "GLFW/glfw3.h"

namespace pesto
{
    struct Application;

    struct WindowHandle
    {
        Application *app;
        GLFWwindow *window{nullptr};

        WindowHandle(Application *mainApp, int sizeX, int sizeY);

        static void poll();

      private:
        void createWindow(int sizeX, int sizeY);
    };
}

#endif // !WINDOW_HPP
