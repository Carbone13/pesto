#ifndef RENDER_HPP
#define RENDER_HPP

#include <cstdint>

#include "../server.hpp"
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"
#include "bgfx/bgfx.h"
#include "glm/glm.hpp"
#include "sprite.hpp"
#include "texture.hpp"

#include "deque"
#include "vector"
#include "map"
#include "stack"

using namespace glm;
using namespace bgfx;

namespace pesto
{
    class Renderer : Server
    {
        VertexLayout spriteVL; // 2D Vertex Layout

        UniformHandle u_texture {kInvalidHandle};

        VertexBufferHandle quadVBH {kInvalidHandle};
        IndexBufferHandle quadIBH {kInvalidHandle};

        std::map<TextureHandle*, std::stack<Sprite*>> spriteBuffer;

        int stride = 64 + 16;

      public:

        int canvasWidth;
        int canvasHeight;

        ProgramHandle shader {kInvalidHandle};
        TextureHandle textureHandle {kInvalidHandle};

        Renderer(Application *app, int canvasWidth, int canvasHeight);

        void initialize();
        void prepare();
        void submit();

        void draw (Sprite *sprite);
    };

    namespace surface
    {
        struct Vertex2D
        {
            float x;
            float y;
            int16_t u;
            int16_t v;
        };

        const Vertex2D quadVertices[] = {
            // pos       // tex
            {0.0f, 1.0f, 0, 0x7fff},
            {1.0f, 0.0f, 0x7fff, 0},
            {0.0f, 0.0f, 0, 0},
            {1.0f, 1.0f, 0x7fff, 0x7fff},
        };

        const uint16_t quadIndices[6] {
            0, 1, 2,
            0, 3, 1
        };
    } // namespace surface
} // namespace pesto

#endif // RENDER_HPP
