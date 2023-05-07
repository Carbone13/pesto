#ifndef PESTO_INITIALIZER_HPP
#define PESTO_INITIALIZER_HPP

#include <cstdint>

namespace pesto
{
    #define DEFAULT_WINDOW_WIDTH 1280
    #define DEFAULT_WINDOW_HEIGHT 720

    #define DEFAULT_CANVAS_WIDTH (16*3)
    #define DEFAULT_CANVAS_HEIGHT (9*3)

    #define MAX_BUFFER_SIZE_DEFAULT 0x00ffffff

    struct Initializer
    {
        int windowWidth = DEFAULT_WINDOW_WIDTH;
        int windowHeight = DEFAULT_WINDOW_HEIGHT;

        int canvasWidth = DEFAULT_CANVAS_WIDTH;
        int canvasHeight = DEFAULT_CANVAS_HEIGHT;

        char* windowName = "Pesto Application";

        uint32_t maxBufferSize = MAX_BUFFER_SIZE_DEFAULT;

        Initializer() = default;
    };
} // namespace pesto
#endif // PESTO_INITIALIZER_HPP
