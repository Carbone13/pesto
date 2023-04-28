#ifndef PESTO_HPP
#define PESTO_HPP

#include "gfx/renderer.hpp"
#include "input/input.hpp"
#include "loader/loader.hpp"
#include "time.hpp"
#include "window/window.hpp"

#include <iostream>

#define DEFAULT_WINDOW_WIDTH 1280
#define DEFAULT_WINDOW_HEIGHT 720

struct Application
{
    WindowHandle windowHandle{this, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT};
    Renderer renderer{this};
    Loader loader{};
    Input input{this};
    Time time{};

    Application() = default;

    void run()
    {
        // Loop
        while (!glfwWindowShouldClose(windowHandle.window))
        {
            // Beginning
            windowHandle.poll();
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

#endif // !PESTO_HPP