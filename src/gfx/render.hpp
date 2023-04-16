#ifndef RENDER_HPP
#define RENDER_HPP

#define GLFW_EXPOSE_NATIVE_WIN32

#include "glm/glm.hpp"
#include "bgfx/bgfx.h"
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

using namespace glm;
using namespace bgfx;

struct Application;

struct Renderer
{
	Application *app;

    Renderer(Application *mainApp);

	void initializeBgfx ();
	
	void prepare ();
	void submit ();
};

#endif // DEBUG
