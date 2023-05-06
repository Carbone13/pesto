#include <iostream>

#include "GLFW/glfw3.h"
#include "bgfx/embedded_shader.h"

#include "pesto/loader.hpp"
#include "pesto/pesto.hpp"

#include "shaders/sprite/shader.h"
#include "sprites/frog.png.h"

#include <random>


std::vector<pesto::Sprite> sprites;

int main()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 50.0);

    pesto::Application app = {};

    pesto::Texture frogTexture = pesto::loader::textureFromData(frog_png, sizeof(frog_png), "frog", BGFX_SAMPLER_MAG_POINT | bgfx::TextureFormat::RGBA32F);

    for (int i = 0; i < 70000; ++i)
    {
        pesto::Sprite sprite {};
        sprite.texture = &frogTexture;
        sprite.textureCoordinate = vec4 (0, 0, 23, 24);
        sprite.setScale(vec2(.07f, .07f));
        sprite.setRotation(dist(mt) * 20.0f);
        sprite.setPosition(vec2(dist(mt) - 25, dist(mt) - 25));

        sprites.push_back(sprite);
    }

    bgfx::EmbeddedShader vs = BGFX_EMBEDDED_SHADER(vs_sprite);
    bgfx::EmbeddedShader fs = BGFX_EMBEDDED_SHADER(fs_sprite);
    bgfx::ProgramHandle sprite = pesto::loader::programFromEmbeddedShaders(&vs, "vs_sprite", &fs, "fs_sprite");

    app.renderer.shader = sprite;

    app.run();
    return 0;
}



void pesto::Application::update()
{
    for (auto & i : sprites)
    {
        i.setRotation(i.getRotation() + 75.0f * this->time.deltaTime());
    }

    if (input.keyPressed(GLFW_KEY_ESCAPE))
    {
        this->close();
    }
}

void pesto::Application::tick()
{
    DEBUG_MILLISECONDS("FRAME: ", this->time.deltaTime(), 0);
    DEBUG_NUMBER("FPS: ", round(1.00f / this->time.deltaTime()), 1);
    DEBUG_NUMBER("DRAW CALL: ", bgfx::getStats()->numDraw, 2);
    DEBUG_NUMBER("MEMORY: ", bgfx::getStats()->gpuMemoryUsed, 3);
}

void pesto::Application::draw()
{
    for (auto & i : sprites)
    {
        renderer.draw(&i);
    }
}
