#ifndef RENDER_HPP
#define RENDER_HPP

#include <cstdint>
#include <stdint.h>

#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"
#include "bgfx/bgfx.h"
#include "glm/glm.hpp"

#include "vertex.hpp"

using namespace glm;
using namespace bgfx;

struct Application;

struct Renderer {
  Application *app;

  explicit Renderer(Application *mainApp);

  void initializeBgfx();

  void prepare();
  void submit();

  VertexLayout spriteVL; // 2D Vertex Layout
  VertexLayout meshVL;   // 3D Vertex Layout

  VertexBufferHandle vbh;
  IndexBufferHandle ibh;

  ProgramHandle shader;
};

struct Util {

  struct Vertex2D {
    float x;
    float y;
    int16_t u;
    int16_t v;

    Vertex2D(float x, float y, int16_t u, int16_t v) : x(x), y(y), u(u), v(v) {}
  };

  struct Vertex3D {
    float x;
    float y;
    float z;
    int16_t u;
    int16_t v;

    Vertex3D(float x, float y, float z, int16_t u, int16_t v)
        : x(x), y(y), z(z), u(u), v(v) {}
  };

  inline static const Vertex2D quadVertices[4]{
      // pos       // tex
      {0.0f, 1.0f, 0, 0x7fff},
      {1.0f, 0.0f, 0x7fff, 0},
      {0.0f, 0.0f, 0, 0},
      {1.0f, 1.0f, 0x7fff, 0x7fff},
  };

  inline static const uint16_t quadIndices[6]{0, 1, 2, 0, 3, 1};
};

struct PosColorVertex {
  float x;
  float y;
  float z;
  uint32_t abgr;
};

static PosColorVertex cubeVertices[] = {
    {-1.0f, 1.0f, 1.0f, 0xff000000},   {1.0f, 1.0f, 1.0f, 0xff0000ff},
    {-1.0f, -1.0f, 1.0f, 0xff00ff00},  {1.0f, -1.0f, 1.0f, 0xff00ffff},
    {-1.0f, 1.0f, -1.0f, 0xffff0000},  {1.0f, 1.0f, -1.0f, 0xffff00ff},
    {-1.0f, -1.0f, -1.0f, 0xffffff00}, {1.0f, -1.0f, -1.0f, 0xffffffff},
};

static const uint16_t cubeTriList[] = {
    0, 1, 2, 1, 3, 2, 4, 6, 5, 5, 6, 7, 0, 2, 4, 4, 2, 6,
    1, 5, 3, 5, 7, 3, 0, 4, 1, 4, 5, 1, 2, 3, 6, 6, 3, 7,
};

#endif // RENDER_HPP
