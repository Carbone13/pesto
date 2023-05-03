#ifndef PESTO_CAMERA_HPP
#define PESTO_CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <glm/ext/matrix_transform.hpp>

#include <bgfx/bgfx.h>

#include "../object/object.hpp"

using namespace glm;

namespace pesto
{
    class Camera : Object
    {
        vec2 screenSize{-1.0, -1.0f};

        mat4 view{1.0f};
        mat4 proj{1.0f};

        vec2 oldPosition{0.0f, 0.0f};

        void recalculate();

      public:
        [[nodiscard]] vec2 getPosition() const
        {
            return position;
        }
        void setPosition(vec2 _position);

        void initialize();
        void prepare();

        explicit Camera(Application *app);
    };
}
#endif // PESTO_CAMERA_HPP
