#ifndef RENDER_HPP
#define RENDER_HPP

#include <cstdint>

#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"
#include "bgfx/bgfx.h"
#include "glm/glm.hpp"

using namespace glm;
using namespace bgfx;

namespace pesto
{
    struct Application;

    struct Renderer
    {
        Application *app;

        explicit Renderer(Application *mainApp);

        void initializeBgfx();

        void prepare();
        void submit();

        VertexLayout spriteVL; // 2D Vertex Layout
        VertexLayout meshVL;   // 3D Vertex Layout

        UniformHandle s_Texture;

        TextureHandle textureHandle;

        VertexBufferHandle vbh;
        IndexBufferHandle ibh;

        ProgramHandle shader;
    };

    namespace rendering
    {
        struct Vertex2D
        {
            float x;
            float y;
            int16_t u;
            int16_t v;

            Vertex2D(float x, float y, int16_t u, int16_t v) : x(x), y(y), u(u), v(v)
            {
            }
        };

        const Vertex2D quadVertices[] = {
            // pos       // tex
            {-1.0f, 1.0f, 0, 0},
            {1.0f, -1.0f, 0x7fff, 0x7fff},
            {-1.0f, -1.0f, 0, 0x7fff},
            {1.0f, 1.0f, 0x7fff, 0},
        };

        const uint16_t quadIndices[6]{0, 2, 3, 3, 2, 1};
    } // namespace rendering

    } // namespace pesto
#endif // RENDER_HPP
