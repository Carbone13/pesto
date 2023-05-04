#ifndef PESTO_TEXTURE_HPP
#define PESTO_TEXTURE_HPP

#include "bgfx/bgfx.h"

namespace pesto
{
    struct Texture
    {
        bgfx::TextureHandle handle;
        bgfx::TextureInfo info;

        Texture (bgfx::TextureHandle handle, bgfx::TextureInfo info) : handle(handle), info(info) {}
    };
}

#endif // PESTO_TEXTURE_HPP
