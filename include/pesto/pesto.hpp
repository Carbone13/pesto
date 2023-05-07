#ifndef PESTO_HPP
#define PESTO_HPP

#include "initializer.hpp"

#include "gfx/renderer.hpp"
#include "input/input.hpp"
#include "window/window.hpp"
#include "camera/camera.hpp"
#include "time.hpp"

namespace pesto
{
    struct Application
    {
        WindowHandle windowHandle;
        Renderer renderer;
        Camera camera;
        Input input;
        Time time;

        explicit Application(Initializer initializer)
        {
            windowHandle = WindowHandle{this, initializer};

            renderer = Renderer{this, initializer};
            renderer.initialize();

            camera = Camera{this};
            camera.initialize();

            input = Input{this};

            time = Time{};
        }

        void run()
        {
            // Loop
            while (!glfwWindowShouldClose(windowHandle.window))
            {
                // Beginning
                glfwPollEvents();
                time.poll();

                // Logic
                update();

                // Physic
                while (time.shouldPhysicsTick())
                {
                    tick();
                    time.registerOneTick();
                }

                // Draw
                renderer.prepare();
                draw();
                renderer.submit();
            }
        }

        virtual void update();
        virtual void tick();
        virtual void draw();

        void close() const
        {
            glfwSetWindowShouldClose(windowHandle.window, 1); // exit
        }
    };
} // namespace pesto

// Util Macros
#include <sstream>
#include <iomanip>

#define DEBUG_MILLISECONDS(title, time, nb) \
(bgfx::dbgTextPrintf(0, nb, ((0x2 + nb) << 4) | 0xF, \
(std::stringstream() << title \
<< std::fixed << std::setprecision(3) \
<< time << " ms").str().c_str()))

#define DEBUG_NUMBER(title, number, nb) \
(bgfx::dbgTextPrintf(0, nb, ((0x2 + nb) << 4) | 0xF, \
(std::stringstream() << title \
<< number).str().c_str()))

#define DEBUG_OUT_OF(title, number, max, nb) \
(bgfx::dbgTextPrintf(0, nb, ((0x2 + nb) << 4) | 0xF, \
(std::stringstream() << title \
<< number << "/" << max).str().c_str()))
#endif // !PESTO_HPP
