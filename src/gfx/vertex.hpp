#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <cstdint>
#include <stdint.h>

struct Vertex2D
{
    float x;
    float y;
    int16_t u;
    int16_t v;

    Vertex2D(float x, float y, int16_t u, int16_t v) : x(x), y(y), u(u), v(v){}
};

struct Vertex3D
{
	float x;
	float y;
	float z;
	int16_t u;
	int16_t v;

	Vertex3D (float x, float y, float z, int16_t u, int16_t v) : x(x), y(y), z(z), u(u), v(v){}
};

#endif //VERTEX_HPP
