#include "loader.hpp"

#include "bgfx/embedded_shader.h"
#include <bimg/decode.h>
#include <iostream>

namespace pesto::loader
{

/// HELPERS
static void check ()
{
    if (_fileReader == nullptr)
    {
        _fileReader = BX_NEW(_allocator, bx::FileReader);
    }
}

static void imageReleaseCb(void *_ptr, void *_userData)
{
    BX_UNUSED(_ptr)
    auto *imageContainer = (bimg::ImageContainer *)_userData;
    bimg::imageFree(imageContainer);
}

static void *load(bx::FileReaderI *reader, bx::AllocatorI *allocator, const char *path, uint32_t *size)
{
    if (bx::open(reader, path))
    {
        auto _size = (uint32_t)bx::getSize(reader);
        void *data = BX_ALLOC(allocator, _size);
        bx::read(reader, data, _size, bx::ErrorAssert{});
        bx::close(reader);
        if (nullptr != size)
        {
            *size = _size;
        }
        return data;
    }
    else
    {
        std::cerr << "[FAIL] - Could not open file at path: " << path << std::endl;
    }

    if (nullptr != size)
    {
        *size = 0;
    }

    return nullptr;
}

static void unload(void *_ptr)
{
    BX_FREE(_allocator, _ptr);
}

/// FUNCTIONS
pesto::Texture textureFromFile(const char *path, const char *name, uint64_t flags)
{
    check();

    uint32_t size;
    void *data = load(_fileReader, _allocator, path, &size);

    pesto::Texture handle = textureFromData(data, size, name, flags);

    unload(data);

    return handle;
}

pesto::Texture textureFromData(const void *data, uint32_t size, const char *name, uint64_t flags)
{
    bgfx::TextureHandle handle = BGFX_INVALID_HANDLE;
    bgfx::TextureInfo info {};

    bimg::ImageContainer *imageContainer = bimg::imageParse(_allocator, data, size);

    if (nullptr != imageContainer)
    {
        const bgfx::Memory *mem =
            bgfx::makeRef(imageContainer->m_data, imageContainer->m_size, imageReleaseCb, imageContainer);

        if (bgfx::isTextureValid(0, false, imageContainer->m_numLayers,
                                 bgfx::TextureFormat::Enum(imageContainer->m_format), flags))
        {
            handle = bgfx::createTexture2D(uint16_t(imageContainer->m_width), uint16_t(imageContainer->m_height),
                                           1 < imageContainer->m_numMips, imageContainer->m_numLayers,
                                           bgfx::TextureFormat::Enum(imageContainer->m_format), flags, mem);
        }

        if (bgfx::isValid(handle))
        {
            bgfx::setName(handle, name);
        }


        bgfx::calcTextureSize(info, uint16_t(imageContainer->m_width), uint16_t(imageContainer->m_height),
                              uint16_t(imageContainer->m_depth), imageContainer->m_cubeMap,
                              1 < imageContainer->m_numMips, imageContainer->m_numLayers,
                              bgfx::TextureFormat::Enum(imageContainer->m_format));

    }

    return pesto::Texture{handle, info};
}

bgfx::ShaderHandle shaderFromFile(const char *path, const char *name)
{
    check();

    uint32_t size;
    void *data = load(_fileReader, _allocator, path, &size);
    bgfx::ShaderHandle handle = shaderFromData(data, size, name);

    unload(data);

    return handle;
}

bgfx::ShaderHandle shaderFromData(const void *data, uint32_t size, const char *name)
{
    const bgfx::Memory *mem = bgfx::makeRef(data, size);

    bgfx::ShaderHandle handle = bgfx::createShader(mem);
    bgfx::setName(handle, name);

    return handle;
}

bgfx::ProgramHandle programFromData(const void *v_data, uint32_t v_size, const char *v_name, const void *f_data,
                                    uint32_t f_size, const char *f_name)
{
    bgfx::ShaderHandle vs = shaderFromData(v_data, v_size, v_name);
    bgfx::ShaderHandle fs = shaderFromData(f_data, f_size, f_name);

    return bgfx::createProgram(vs, fs, true);
}

bgfx::ProgramHandle programFromFiles(const char *v_path, const char *v_name, const char *f_path, const char *f_name)
{
    bgfx::ShaderHandle vs = shaderFromFile(v_path, v_name);
    bgfx::ShaderHandle fs = shaderFromFile(f_path, f_name);

    return bgfx::createProgram(vs, fs, true);
}
bgfx::ProgramHandle programFromEmbeddedShaders(bgfx::EmbeddedShader *v, const char *v_name,
                                               bgfx::EmbeddedShader *f, const char *f_name)
{
    if(bgfx::getRendererType() == bgfx::RendererType::Count || bgfx::getRendererType() == bgfx::RendererType::Noop)
    {
        std::cerr << "[FAIL] - Can't load embedded shader if bgfx is not initialized !" << std::endl;
    }

    bgfx::ShaderHandle vs = bgfx::createEmbeddedShader(v, bgfx::getRendererType(), v_name);
    bgfx::ShaderHandle fs = bgfx::createEmbeddedShader(f, bgfx::getRendererType(), f_name);

    return bgfx::createProgram(vs, fs, true);
}

} // namespace pesto::loader