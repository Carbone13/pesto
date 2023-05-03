#ifndef PESTO_TIME_HPP
#define PESTO_TIME_HPP

#include "GLFW/glfw3.h"

namespace pesto
{
    class Time
    {
        float lastTime{0};
        float accumulator{0};

        float delta{0};
        float fixedDelta = 1.0f / 30.0f;

      public:
        [[nodiscard]] float deltaTime() const
        {
            return delta;
        }
        [[nodiscard]] float fixedDeltaTime() const
        {
            return fixedDelta;
        }

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

        [[nodiscard]] bool shouldPhysicsTick() const
        {
            return accumulator >= fixedDelta;
        }
    };
} // namespace pesto

#endif // PESTO_TIME_HPP
