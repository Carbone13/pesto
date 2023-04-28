#ifndef PESTO_LOADER_HPP
#define PESTO_LOADER_HPP

#include "bgfx/bgfx.h"

#include <bx/bx.h>
#include <bx/file.h>
#include <bx/sort.h>

#include <bimg/decode.h>

#include <cstdio>

#define IMPORT_COMPILED_SHADER(NAME) (include <vs_##NAME.sc.glsl.bin.h>)

//#include <vs_name.sc.essl.bin.h>\
//#include <vs_name.sc.spv.bin.h>\
//#include <fs_name.sc.glsl.bin.h>\
//#include <fs_name.sc.essl.bin.h>\
//#include <fs_name.sc.spv.bin.h>\
//#if defined(_WIN32)\
//#include <vs_name.sc.dx9.bin.h>\
//#include <vs_name.sc.dx11.bin.h>\
//#include <fs_name.sc.dx9.bin.h>\
//#include <fs_name.sc.dx11.bin.h>\
//#endif //  defined(_WIN32)\
//#if __APPLE__\
//#include <vs_name.sc.mtl.bin.h>\
//#include <fs_name.sc.mtl.bin.h>\
//#endif // __APPLE__\


#define LOAD_COMPILED_SHADER

struct Loader
{
    bx::FileReaderI *fileReader = nullptr;
    bx::AllocatorI *g_allocator = getDefaultAllocator();

    static bx::AllocatorI *getDefaultAllocator()
    {
        BX_PRAGMA_DIAGNOSTIC_PUSH()
        BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wshadow")
        static bx::DefaultAllocator s_allocator;
        return &s_allocator;
        BX_PRAGMA_DIAGNOSTIC_POP()
    }

    bgfx::TextureHandle loadTexture(bx::FileReaderI *_reader, const char *_filePath, uint64_t _flags, uint8_t _skip,
                                    bgfx::TextureInfo *_info, bimg::Orientation::Enum *_orientation);
    void unload(void *_ptr);

  public:
    const char *generatedDirectory;

    Loader()
    {
        fileReader = BX_NEW(g_allocator, bx::FileReader);
    }

    bgfx::TextureHandle loadTexture(const char *_name, uint64_t _flags = BGFX_TEXTURE_NONE | BGFX_SAMPLER_NONE,
                                    uint8_t _skip = 0, bgfx::TextureInfo *_info = nullptr,
                                    bimg::Orientation::Enum *_orientation = NULL);

    bgfx::ShaderHandle loadShader(const char *_name);
    bgfx::ProgramHandle loadProgram(const char *PROGRAM);

    const bgfx::Memory *loadMem(const char *_filePath);
    void *loadMem(const char *_filePath, uint32_t *_size);
};

#endif // PESTO_LOADER_HPP
