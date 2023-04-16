#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <cstdint>

struct Vertex
{
    float x;
    float y;
    int16_t u;
    int16_t v;

    Vertex(float x, float y, int16_t u, int16_t v) : x(x), y(y), u(u), v(v){}
};

#endif //VERTEX_HPP
