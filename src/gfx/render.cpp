
#include "render.hpp"
#include "pesto.hpp"

#include <iostream>

Renderer::Renderer(Application *mainApp)
{
    app = mainApp;
    initializeBgfx();
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
        std::cerr << " - [FAIL] : Could not initialize BGFX" << std::endl;
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
	bgfx::frame();
}
