#ifndef PESTO_RESOURCE_LOADING_HPP
#define PESTO_RESOURCE_LOADING_HPP

#include "bgfx/bgfx.h"

#include <bx/bx.h>
#include <bx/file.h>
#include <bx/sort.h>

#include "bimg/bimg.h"

static bx::AllocatorI* getDefaultAllocator()
{
    BX_PRAGMA_DIAGNOSTIC_PUSH();
    BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4459); // warning C4459: declaration of 'allocator' hides global declaration

    static bx::DefaultAllocator allocator;
    return &allocator;
    BX_PRAGMA_DIAGNOSTIC_POP();
}

namespace pesto::loader
{
const uint64_t pixelArtFlags =
    BGFX_SAMPLER_MAG_POINT |
    BGFX_SAMPLER_MIN_POINT |
    BGFX_SAMPLER_UVW_CLAMP;

    static bx::FileReaderI* _fileReader = nullptr;
    static bx::AllocatorI* _allocator = getDefaultAllocator();

    static void check ()
    {
        if (_fileReader == nullptr)
        {
            _fileReader = BX_NEW(_allocator, bx::FileReader);
        }
    }

    bgfx::TextureHandle loadTexture(const char *_name, uint64_t _flags = BGFX_TEXTURE_NONE | BGFX_SAMPLER_NONE,
                                uint8_t _skip = 0, bgfx::TextureInfo *_info = nullptr,
                                bimg::Orientation::Enum *_orientation = nullptr);
} // namespace pesto



#define LOAD_PROGRAM(NAME)                                                                                             \
        []() {                                                                                                             \
            const bgfx::EmbeddedShader fs = BGFX_EMBEDDED_SHADER(fs_##NAME);                                               \
            const bgfx::EmbeddedShader vs = BGFX_EMBEDDED_SHADER(vs_##NAME);                                               \
            auto fs_handle =                                                                                               \
                createEmbeddedShader(&fs, bgfx::getRendererType(), (std::stringstream() << "fs_" << #NAME).str().data());  \
            auto vs_handle =                                                                                               \
                createEmbeddedShader(&vs, bgfx::getRendererType(), (std::stringstream() << "vs_" << #NAME).str().data());  \
            return bgfx::createProgram(vs_handle, fs_handle, true);                                                        \
        }()

#endif // PESTO_RESOURCE_LOADING_HPP
