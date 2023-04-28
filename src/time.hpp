#ifndef PESTO_TIME_HPP
#define PESTO_TIME_HPP

#include "GLFW/glfw3.h"

struct Time
{
    float delta;
    float fixedDelta = 1.0f / 30.0f;

    void poll()
    {
        auto now = static_cast<float>(glfwGetTime());

        delta = now - lastTime;
        lastTime = now;

        accumulator += delta;
    }

    void registerOneTick()
    {
        accumulator -= fixedDelta;
    }

    bool shouldPhysicsTick()
    {
        return accumulator >= fixedDelta;
    };

  private:
    float lastTime{0};
    float accumulator{0};
};

#endif // PESTO_TIME_HPP
