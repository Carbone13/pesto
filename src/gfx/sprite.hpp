#ifndef PESTO_SPRITE_HPP
#define PESTO_SPRITE_HPP

#include "../object/object.hpp"
#include "bgfx/bgfx.h"
#include "texture.hpp"

namespace pesto
{
    class Sprite : public Object
    {
      public:
        Sprite () : Object(nullptr) {}

        Texture *texture;
        vec4 textureCoordinate;
    };
}

#endif // PESTO_SPRITE_HPP
