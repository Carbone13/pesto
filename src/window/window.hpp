#ifndef PESTO_WINDOW_HPP
#define PESTO_WINDOW_HPP

#include "GLFW/glfw3.h"
#include "../server.hpp"

namespace pesto
{
    class WindowHandle : public Server
    {
      public:
        WindowHandle () = default;
        WindowHandle(Application *app, Initializer initializer);

        GLFWwindow *window{nullptr};
    };
}

#endif // PESTO_WINDOW_HPP
