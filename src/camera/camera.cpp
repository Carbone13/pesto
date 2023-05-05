#include "pesto.hpp"

namespace pesto
{
    void Camera::onTransformChanged()
    {
        recalculate();
    }

    void Camera::recalculate()
    {
        view = glm::translate(glm::mat4(1.0f), glm::vec3(-getPosition().x, getPosition().y, 0.0f));
    }

    void Camera::prepare()
    {
        bgfx::setViewTransform(0, reinterpret_cast<void *>(&view), reinterpret_cast<void *>(&proj));

        int width;
        int height;
        glfwGetWindowSize(app->windowHandle.window, &width, &height);

        bgfx::setViewRect(0, 0, 0, width, height);
    }

    Camera::Camera(Application *app) : Object(app)
    {
    }

    void Camera::initialize()
    {
        screenSize = vec2(static_cast<float>(app->renderer.canvasWidth), static_cast<float>(app->renderer.canvasHeight));
        recalculate();

        proj = glm::ortho(-screenSize.x / 2.0f, +screenSize.x / 2.0f, +screenSize.y / 2.0f, -screenSize.y / 2.0f, -1000.0f,
                          1000.0f);
    }
}