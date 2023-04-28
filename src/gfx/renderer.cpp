#include "GLFW/glfw3.h"
#include "bgfx/bgfx.h"
#define GLFW_EXPOSE_NATIVE_WIN32

#include "pesto.hpp"
#include "gfx/renderer.hpp"

#include <iostream>

Renderer::Renderer(Application *mainApp)
{
    app = mainApp;
    initializeBgfx();

    spriteVL.begin();
    spriteVL.add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float);
    spriteVL.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Int16, true, true);
    spriteVL.end();

//    meshVL.begin();
//    meshVL.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float);
//    meshVL.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Int16, true, true);
//    meshVL.end();
    meshVL.begin()
        .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
        .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
        .end();


}

void Renderer::initializeBgfx()
{
    bgfx::Init i{};
    PlatformData pd{};
    pd.nwh = glfwGetWin32Window(app->windowHandle.window);

    i.type = bgfx::RendererType::Count; // automatically choose a renderer
    i.resolution.width = 1280;
    i.resolution.height = 720;
    i.resolution.reset = BGFX_RESET_VSYNC; // activate vsync
    i.platformData = pd;

    if (!bgfx::init(i))
    {
        std::cerr << "[FAIL] : Could not initialize BGFX" << std::endl;
    }

    bgfx::reset(1280, 720, BGFX_RESET_VSYNC, i.resolution.format);
    bgfx::setDebug(BGFX_DEBUG_TEXT);
    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x003030FF, 1.0f, 0);
    bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);
}

void Renderer::prepare()
{
    bgfx::touch(0);
}

void Renderer::submit()
{
    vbh = bgfx::createVertexBuffer(bgfx::makeRef(cubeVertices, sizeof(cubeVertices)), meshVL);
    ibh = bgfx::createIndexBuffer(bgfx::makeRef(cubeTriList, sizeof(cubeTriList)));

    const bx::Vec3 at = {0.0f, 0.0f, 0.0f};
    const bx::Vec3 eye = {0.0f, 0.0f, -5.0f};
    float view[16];
    bx::mtxLookAt(view, eye, at);
    float proj[16];
    bx::mtxProj(proj, 60.0f, float(1280) / float(720), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
    bgfx::setViewTransform(0, view, proj);
    float mtx[16];
    bx::mtxRotateXY(mtx, glfwGetTime() * 0.1f, glfwGetTime() * 0.1f);
    bgfx::setTransform(mtx);

    // auto vbh = bgfx::createVertexBuffer(bgfx::makeRef(Util::quadVertices, sizeof(Util::quadVertices)), spriteVL);
    // auto ibh = bgfx::createIndexBuffer(bgfx::makeRef(Util::quadIndices, sizeof(Util::quadIndices)));

    // Set vertex and index buffer.
    bgfx::setVertexBuffer(0, vbh);
    bgfx::setIndexBuffer(ibh);

    // Set render states.
    bgfx::setState(BGFX_STATE_DEFAULT);

    // Submit primitive for rendering to view 0.
    bgfx::submit(0, shader);

    bgfx::frame();

    destroy(vbh);
    destroy(ibh);
}
