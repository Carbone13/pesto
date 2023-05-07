#ifndef PESTO_RESOURCE_LOADING_HPP
#define PESTO_RESOURCE_LOADING_HPP

#include "../../src/gfx/texture.hpp"

#include "bgfx/bgfx.h"
#include "bgfx/embedded_shader.h"

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
    static bx::FileReaderI* _fileReader = nullptr;
    static bx::AllocatorI* _allocator = getDefaultAllocator();
    ////// TEXTURE LOADING

    /// Load a Texture from raw data
    /// \param data Pointer to first byte of data
    /// \param size Total size of data
    /// \param name Name for BGFX debug
    /// \param flags Texture flags
    /// \param outputInfo Pointer to a TextureInfo
    pesto::Texture textureFromData (const void *data, uint32_t size, const char *name, uint64_t flags = 0);
    /// Load a Texture from file (.bin, .dds, .jpg, .png...)
    /// \param path Path to data file
    /// \param name Name for BGFX debug
    /// \param flags Texture flags
    /// \param outputInfo Pointer to a TextureInfo
    pesto::Texture textureFromFile (const char *path, const char *name, uint64_t flags = 0);


    ////// SHADER LOADING

    /// Load a Shader from raw data
    /// \param data Pointer to first byte of data
    /// \param size Total size of data
    /// \param name Name for BGFX debug
    bgfx::ShaderHandle shaderFromData(const void *data, uint32_t size, const char *name);
    /// Load a Shader from file (compiled .bin only !)
    /// \param path Path to data file
    /// \param name Name for BGFX debug
    bgfx::ShaderHandle shaderFromFile(const char *path, const char *name);


    bgfx::ProgramHandle programFromData (const void *v_data, uint32_t v_size, const char *v_name,
                                         const void *f_data, uint32_t f_size, const char *f_name);
    bgfx::ProgramHandle programFromFiles (const char *v_path, const char *v_name, const char *f_path, const char *f_name);
    bgfx::ProgramHandle programFromEmbeddedShaders (bgfx::EmbeddedShader *v, const char *v_name, bgfx::EmbeddedShader *f, const char *f_name);

} // namespace pesto

#endif // PESTO_RESOURCE_LOADING_HPP
