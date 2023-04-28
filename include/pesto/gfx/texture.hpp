#ifndef PESTO_TEXTURE_HPP
#define PESTO_TEXTURE_HPP

#include "bgfx/bgfx.h"

struct Texture
{
    bgfx::TextureHandle textureHandle;
    bgfx::TextureInfo textureInfo;
};

#endif // PESTO_TEXTURE_HPP
