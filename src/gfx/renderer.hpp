#ifndef RENDER_HPP
#define RENDER_HPP

#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"
#include "bgfx/bgfx.h"
#include "glm/glm.hpp"

using namespace glm;
using namespace bgfx;

struct Application;

struct Renderer
{
    Application *app;

    Renderer(Application *mainApp);

    void initializeBgfx();

    void prepare();
    void submit();

    VertexLayout spriteVL; // 2D Vertex Layout
    VertexLayout meshVL;   // 3D Vertex Layout
};

#endif // DEBUG
