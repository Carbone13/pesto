#include "loader.hpp"
#include "pesto.hpp"

void* load(bx::FileReaderI* _reader, bx::AllocatorI* _allocator, const char* _filePath, uint32_t* _size)
{
    if (bx::open(_reader, _filePath) )
    {
        auto size = (uint32_t)bx::getSize(_reader);
        void* data = BX_ALLOC(_allocator, size);
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

void Loader::unload(void* _ptr)
{
    BX_FREE(g_allocator, _ptr);
}


static void imageReleaseCb(void* _ptr, void* _userData)
{
    BX_UNUSED(_ptr)
    auto* imageContainer = (bimg::ImageContainer*)_userData;
    bimg::imageFree(imageContainer);
}

bgfx::TextureHandle Loader::loadTexture(bx::FileReaderI* _reader, const char* _filePath, uint64_t _flags, uint8_t _skip, bgfx::TextureInfo* _info, bimg::Orientation::Enum* _orientation)
{
    BX_UNUSED(_skip)
    bgfx::TextureHandle handle = BGFX_INVALID_HANDLE;

    uint32_t size;
    void* data = load(_reader, g_allocator, _filePath, &size);
    if (nullptr != data)
    {
        bimg::ImageContainer* imageContainer = bimg::imageParse(g_allocator, data, size);

        if (nullptr != imageContainer)
        {
            if (nullptr != _orientation)
            {
                *_orientation = imageContainer->m_orientation;
            }

            const bgfx::Memory* mem = bgfx::makeRef(
                    imageContainer->m_data
                    , imageContainer->m_size
                    , imageReleaseCb
                    , imageContainer
            );

            unload(data);

            if (1 < imageContainer->m_depth)
            {
                handle = bgfx::createTexture3D(
                        uint16_t(imageContainer->m_width)
                        , uint16_t(imageContainer->m_height)
                        , uint16_t(imageContainer->m_depth)
                        , 1 < imageContainer->m_numMips
                        , bgfx::TextureFormat::Enum(imageContainer->m_format)
                        , _flags
                        , mem
                );
            }
            else if (bgfx::isTextureValid(0, false, imageContainer->m_numLayers, bgfx::TextureFormat::Enum(imageContainer->m_format), _flags) )
            {
                handle = bgfx::createTexture2D(
                        uint16_t(imageContainer->m_width)
                        , uint16_t(imageContainer->m_height)
                        , 1 < imageContainer->m_numMips
                        , imageContainer->m_numLayers
                        , bgfx::TextureFormat::Enum(imageContainer->m_format)
                        , _flags
                        , mem
                );
            }

            if (bgfx::isValid(handle) )
            {
                bgfx::setName(handle, _filePath);
            }

            if (nullptr != _info)
            {
                bgfx::calcTextureSize(
                        *_info
                        , uint16_t(imageContainer->m_width)
                        , uint16_t(imageContainer->m_height)
                        , uint16_t(imageContainer->m_depth)
                        , imageContainer->m_cubeMap
                        , 1 < imageContainer->m_numMips
                        , imageContainer->m_numLayers
                        , bgfx::TextureFormat::Enum(imageContainer->m_format)
                );
            }
        }
    }

    return handle;
}

bgfx::TextureHandle Loader::loadTexture(const char* _name, uint64_t _flags, uint8_t _skip, bgfx::TextureInfo* _info, bimg::Orientation::Enum* _orientation)
{
    return loadTexture(fileReader, _name, _flags, _skip, _info, _orientation);
}
