#define GLFW_EXPOSE_NATIVE_WIN32
#include "pesto.hpp"
#include "renderer.hpp"

#include <iostream>

namespace pesto
{
    Renderer::Renderer(Application *app, int canvasWidth, int canvasHeight) : Server(app)
    {
        this->canvasWidth = canvasWidth;
        this->canvasHeight = canvasHeight;

        spriteVL.begin();
        spriteVL.add(bgfx::Attrib::Position,2, bgfx::AttribType::Float);
        spriteVL.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Int16, true, true);
        spriteVL.end();
    }

    void Renderer::initialize()
    {
        bgfx::Init i{};
        PlatformData pd{};
        pd.nwh = glfwGetWin32Window(app->windowHandle.window);

        i.type = bgfx::RendererType::Count; // automatically choose a renderer

        int width;
        int height;
        glfwGetWindowSize(app->windowHandle.window, &width, &height);

        i.resolution.width = width;
        i.resolution.height = height;
        i.resolution.reset = BGFX_RESET_VSYNC; // activate vsync
        i.platformData = pd;

        if (!bgfx::init(i))
        {
            std::cerr << "[FAIL] : Could not initialize BGFX" << std::endl;
        }

        bgfx::reset(width, height, BGFX_RESET_VSYNC, i.resolution.format);
        bgfx::setDebug(BGFX_DEBUG_TEXT);
        bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x003030FF, 1.0f, 0);
        bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);

        u_texture = bgfx::createUniform("u_texture", bgfx::UniformType::Sampler);

        quadVBH = bgfx::createVertexBuffer(bgfx::makeRef(surface::quadVertices, sizeof(surface::quadVertices)), Renderer::spriteVL);
        quadIBH = bgfx::createIndexBuffer(bgfx::makeRef(surface::quadIndices, sizeof(surface::quadIndices)));
    }

    void Renderer::prepare()
    {
        bgfx::touch(0);
        app->camera.prepare();
    }

    void Renderer::submit()
    {
        // SPRITE BATCHING
        bgfx::setVertexBuffer(0, quadVBH);
        bgfx::setIndexBuffer(quadIBH);

        for(auto& command : spriteBuffer)
        {
            TextureHandle texture = *command.first;
            auto sprites = &command.second;

            // Set batch texture
            bgfx::setTexture(0, u_texture, texture);

            while(!sprites->empty())
            {
                auto maxSpriteInCall = bgfx::getAvailInstanceDataBuffer(sprites->size(), stride);

                bgfx::InstanceDataBuffer idb{};
                bgfx::allocInstanceDataBuffer(&idb, maxSpriteInCall, stride);
                uint8_t *data = idb.data;

                for (int i = 0; i < maxSpriteInCall; i++)
                {
                    Sprite sprite = *sprites->top();
                    sprites->pop();

                    auto spriteArea = sprite.textureCoordinate;
                    auto scale = sprite.scale * vec2(spriteArea.z,spriteArea.w);

                    auto* mtx = (mat4x4*)(float*)data;

                    // translate
                    *mtx = translate(mat4x4{1.0f}, vec3(sprite.position, 0.0f));
                    // rotate (centered pivot)
                    *mtx = translate(*mtx, vec3(0.5f * scale.x, 0.5f * scale.y, 0.0f));
                    *mtx = rotate(*mtx, glm::radians(sprite.rotation), vec3(0.0f, 0.0f, 1.0f));
                    *mtx = translate(*mtx, vec3(-0.5f * scale.x, -0.5f * scale.y, 0.0f));
                    // scale
                    *mtx = glm::scale(*mtx, vec3(scale, 1.0f));

                    auto* area = (float*)&data[64];
                    area[0] = spriteArea.x / (float)sprite.texture->info.width;
                    area[1] = spriteArea.y / (float)sprite.texture->info.height;
                    area[2] = spriteArea.z / (float)sprite.texture->info.width;
                    area[3] = spriteArea.w / (float)sprite.texture->info.height;

                    data += stride;
                }

                bgfx::setInstanceDataBuffer(&idb);
                // Set render states.
                bgfx::setState(BGFX_STATE_DEFAULT);
                // Submit primitive for rendering to view 0.
                bgfx::submit(0, shader);
            }
        }

        bgfx::frame();
    }

    void Renderer::draw(Sprite *sprite)
    {
        spriteBuffer[&(sprite->texture->handle)].push(sprite);
    }
}