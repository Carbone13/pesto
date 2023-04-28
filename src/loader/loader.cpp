#include "loader.hpp"
#include "bgfx/bgfx.h"
#include "pesto.hpp"
#include <filesystem>
#include <ostream>
#include <string>

void *Loader::loadMem(const char *_filePath, uint32_t *_size)
{
    if (bx::open(fileReader, _filePath))
    {
        uint32_t size = (uint32_t)bx::getSize(fileReader);
        void *data = bx::alloc(g_allocator, size);
        bx::read(fileReader, data, size, bx::ErrorAssert{});
        bx::close(fileReader);

        if (NULL != _size)
        {
            *_size = size;
        }
        return data;
    }

    return NULL;
}

const bgfx::Memory *Loader::loadMem(const char *_filePath)
{
    if (bx::open(fileReader, _filePath))
    {
        uint32_t size = (uint32_t)bx::getSize(fileReader);
        const bgfx::Memory *mem = bgfx::alloc(size + 1);
        bx::read(fileReader, mem->data, size, bx::ErrorAssert{});
        bx::close(fileReader);
        mem->data[mem->size - 1] = '\0';
        return mem;
    }

    std::cerr << _filePath << std::endl;

    return NULL;
}

void *load(bx::FileReaderI *_reader, bx::AllocatorI *_allocator, const char *_filePath, uint32_t *_size)
{
    if (bx::open(_reader, _filePath))
    {
        auto size = (uint32_t)bx::getSize(_reader);
        void *data = BX_ALLOC(_allocator, size);
        bx::read(_reader, data, size, bx::ErrorAssert{});
        bx::close(_reader);
        if (nullptr != _size)
        {
            *_size = size;
        }
        return data;
    }
    else
    {
    }

    if (nullptr != _size)
    {
        *_size = 0;
    }

    return nullptr;
}

void Loader::unload(void *_ptr)
{
    BX_FREE(g_allocator, _ptr);
}

static void imageReleaseCb(void *_ptr, void *_userData)
{
    BX_UNUSED(_ptr)
    auto *imageContainer = (bimg::ImageContainer *)_userData;
    bimg::imageFree(imageContainer);
}

bgfx::TextureHandle Loader::loadTexture(bx::FileReaderI *_reader, const char *_filePath, uint64_t _flags, uint8_t _skip,
                                        bgfx::TextureInfo *_info, bimg::Orientation::Enum *_orientation)
{
    BX_UNUSED(_skip)
    bgfx::TextureHandle handle = BGFX_INVALID_HANDLE;

    uint32_t size;
    void *data = load(_reader, g_allocator, _filePath, &size);
    if (nullptr != data)
    {
        bimg::ImageContainer *imageContainer = bimg::imageParse(g_allocator, data, size);

        if (nullptr != imageContainer)
        {
            if (nullptr != _orientation)
            {
                *_orientation = imageContainer->m_orientation;
            }

            const bgfx::Memory *mem =
                bgfx::makeRef(imageContainer->m_data, imageContainer->m_size, imageReleaseCb, imageContainer);

            unload(data);

            if (1 < imageContainer->m_depth)
            {
                handle = bgfx::createTexture3D(uint16_t(imageContainer->m_width), uint16_t(imageContainer->m_height),
                                               uint16_t(imageContainer->m_depth), 1 < imageContainer->m_numMips,
                                               bgfx::TextureFormat::Enum(imageContainer->m_format), _flags, mem);
            }
            else if (bgfx::isTextureValid(0, false, imageContainer->m_numLayers,
                                          bgfx::TextureFormat::Enum(imageContainer->m_format), _flags))
            {
                handle = bgfx::createTexture2D(uint16_t(imageContainer->m_width), uint16_t(imageContainer->m_height),
                                               1 < imageContainer->m_numMips, imageContainer->m_numLayers,
                                               bgfx::TextureFormat::Enum(imageContainer->m_format), _flags, mem);
            }

            if (bgfx::isValid(handle))
            {
                bgfx::setName(handle, _filePath);
            }

            if (nullptr != _info)
            {
                bgfx::calcTextureSize(*_info, uint16_t(imageContainer->m_width), uint16_t(imageContainer->m_height),
                                      uint16_t(imageContainer->m_depth), imageContainer->m_cubeMap,
                                      1 < imageContainer->m_numMips, imageContainer->m_numLayers,
                                      bgfx::TextureFormat::Enum(imageContainer->m_format));
            }
        }
    }

    return handle;
}

bgfx::TextureHandle Loader::loadTexture(const char *_name, uint64_t _flags, uint8_t _skip, bgfx::TextureInfo *_info,
                                        bimg::Orientation::Enum *_orientation)
{
    return loadTexture(fileReader, _name, _flags, _skip, _info, _orientation);
}

bgfx::ShaderHandle Loader::loadShader(const char *_name)
{
    char filePath[512];

    const char *shaderPath = "???";

    switch (bgfx::getRendererType())
    {
    case bgfx::RendererType::Noop:
    case bgfx::RendererType::Direct3D9:
        shaderPath = "shaders/dx9/";
        break;
    case bgfx::RendererType::Direct3D11:
    case bgfx::RendererType::Direct3D12:
        shaderPath = "shaders/dx11/";
        break;
    case bgfx::RendererType::Agc:
    case bgfx::RendererType::Gnm:
        shaderPath = "shaders/pssl/";
        break;
    case bgfx::RendererType::Metal:
        shaderPath = "shaders/metal/";
        break;
    case bgfx::RendererType::Nvn:
        shaderPath = "shaders/nvn/";
        break;
    case bgfx::RendererType::OpenGL:
        shaderPath = "shaders/glsl/";
        break;
    case bgfx::RendererType::OpenGLES:
        shaderPath = "shaders/essl/";
        break;
    case bgfx::RendererType::Vulkan:
        shaderPath = "shaders/spirv/";
        break;
    case bgfx::RendererType::WebGPU:
        shaderPath = "shaders/spirv/";
        break;

    case bgfx::RendererType::Count:
        BX_ASSERT(false, "You should not be here!");
        break;
    }

    bx::strCopy(filePath, BX_COUNTOF(filePath), generatedDirectory);
    bx::strCat(filePath, BX_COUNTOF(filePath), shaderPath);
    bx::strCat(filePath, BX_COUNTOF(filePath), _name);
    // bx::strCat(filePath, BX_COUNTOF(filePath), ".bin");

    bgfx::ShaderHandle handle = bgfx::createShader(loadMem(filePath));
    bgfx::setName(handle, _name);

    return handle;
}

bgfx::ProgramHandle Loader::loadProgram(const char *PROGRAM)
{
    auto vsh = loadShader((std::string("vs_") + PROGRAM + std::string(".bin")).c_str());
    auto fsh = loadShader((std::string("fs_") + PROGRAM + std::string(".bin")).c_str());

    return bgfx::createProgram(vsh, fsh, true);
}
