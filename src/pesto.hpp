#ifndef PESTO_HPP
#define PESTO_HPP

#include "gfx/render.hpp"
#include "time.hpp"
#include "window/window.hpp"
#include "input/input.hpp"
#include <iostream>

#define DEFAULT_WINDOW_WIDTH 1280
#define DEFAULT_WINDOW_HEIGHT 720


struct Application
{
    WindowHandle windowHandle {this, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT};
    Renderer renderer {this};
	Input input {this};
    Time time {};

    Application ()
    {
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

};

#endif // !PESTO_HPP
