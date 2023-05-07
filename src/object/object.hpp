#ifndef PESTO_OBJECT_HPP
#define PESTO_OBJECT_HPP

#include <glm/glm.hpp>
#include "glm/ext/matrix_transform.hpp"

#include <functional>

using namespace glm;

namespace pesto
{
    struct Application;

    class Object
    {
      public:
        Object () = default;
        explicit Object(Application *app) { this->app = app; }

        void setPosition(vec2 new_position)
        {
            onTransformChanged();
            position = new_position;
        }
        vec2 getPosition () { return position; }

        void setScale(vec2 new_scale)
        {
            onTransformChanged();
            scale = new_scale;
        }
        vec2 getScale () { return scale; }

        void setRotation(float new_rotation)
        {
            onTransformChanged();
            rotation = new_rotation;
        }
        [[nodiscard]] float getRotation () const { return rotation; }

      protected:
        Application *app;

        virtual void onTransformChanged() {}

      private:
        vec2 position{0.0f, 0.0f};
        vec2 scale {1.0f};
        float rotation {0.0f};
    };
}
#endif // PESTO_OBJECT_HPP
