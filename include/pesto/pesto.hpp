#ifndef PESTO_HPP
#define PESTO_HPP

#include "../../src/gfx/renderer.hpp"
#include "../../src/input/input.hpp"
#include "../../src/time.hpp"
#include "../../src/window/window.hpp"
#include "../../src/camera/camera.hpp"

#include <cstdio>
#include <iostream>

namespace pesto
{
    #define DEFAULT_WINDOW_WIDTH 1280
    #define DEFAULT_WINDOW_HEIGHT 720

    #define DEFAULT_CANVAS_WIDTH 16*3
    #define DEFAULT_CANVAS_HEIGHT 9*3

    struct Application
    {
        WindowHandle windowHandle {this, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT};
        Renderer renderer {this, DEFAULT_CANVAS_WIDTH, DEFAULT_CANVAS_HEIGHT};
        Camera camera {this};
        Input input {this};
        Time time {};

        Application()
        {
            renderer.initialize();
            camera.initialize();
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

#endif // !PESTO_HPP
