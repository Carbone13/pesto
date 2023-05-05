#ifndef PESTO_SPRITE_HPP
#define PESTO_SPRITE_HPP

#include "../object/object.hpp"
#include "bgfx/bgfx.h"
#include "texture.hpp"

namespace pesto
{
    class Sprite : public Object
    {
        mat4x4 renderingTransform;

        void onTransformChanged () override
        {
            auto scale = vec3(textureCoordinate.z * getScale().x, textureCoordinate.w * getScale().y, 1.0f);
            // translate
            renderingTransform = translate(mat4x4{1.0f}, vec3(getPosition(), 0.0f));
            // rotate (centered pivot)
            renderingTransform = translate(renderingTransform, vec3(0.5f * scale.x, 0.5f * scale.y, 0.0f));
            renderingTransform = rotate(renderingTransform, glm::radians(getRotation()), vec3(0.0f, 0.0f, 1.0f));
            renderingTransform = translate(renderingTransform, vec3(-0.5f * scale.x, -0.5f * scale.y, 0.0f));
            // scale
            renderingTransform = glm::scale(renderingTransform, scale);
        }

      public:
        Sprite (Texture *texture = nullptr, vec4 textureCoordinate = vec4(0.0f)) : renderingTransform(mat4x4{1.0f}), texture(texture),
              textureCoordinate(textureCoordinate), Object(nullptr) {}

        mat4x4 getRenderingTransform () { return renderingTransform; }

        Texture *texture;
        vec4 textureCoordinate;
    };
}

#endif // PESTO_SPRITE_HPP
