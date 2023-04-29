#ifndef PESTO_HPP
#define PESTO_HPP

#include "../../src/gfx/renderer.hpp"
#include "../../src/input/input.hpp"
#include "../../src/time.hpp"
#include "../../src/window/window.hpp"

#include <bx/bx.h>
#include <bx/file.h>
#include <bx/sort.h>
#include <bimg/decode.h>

#include <cstdio>
#include <iostream>

namespace pesto
{
    #define DEFAULT_WINDOW_WIDTH 1280
    #define DEFAULT_WINDOW_HEIGHT 720

    struct Application
    {
        WindowHandle windowHandle {this, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT};
        Renderer renderer {this};
        Input input {this};
        Time time {};

        Application()
        {
            _fileReader = BX_NEW(_allocator, bx::FileReader);
        }

        void run()
        {
            // Loop
            while (!glfwWindowShouldClose(windowHandle.window))
            {
                // Beginning
                pesto::WindowHandle::poll();
                time.poll();

                // Logic
                update();

                // Physic
                while (time.shouldPhysicsTick())
                {
                    tick();
                    time.registerOneTick();
                }

                // Draw
                renderer.prepare();
                draw();
                renderer.submit();
            }
        }

        virtual void update();
        virtual void tick();
        virtual void draw();

        void close() const
        {
            glfwSetWindowShouldClose(windowHandle.window, 1); // exit
        }

        bx::FileReaderI* getFileReader() { return _fileReader; }
        bx::AllocatorI*  getAllocator() { return _allocator; }

      private:
        bx::FileReaderI* _fileReader = nullptr;
        bx::AllocatorI* _allocator = getDefaultAllocator();

        static bx::AllocatorI* getDefaultAllocator()
        {
            BX_PRAGMA_DIAGNOSTIC_PUSH();
            BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4459); // warning C4459: declaration of 'allocator' hides global declaration

            static bx::DefaultAllocator allocator;
            return &allocator;

            BX_PRAGMA_DIAGNOSTIC_POP();
        }

    };
} // namespace pesto

// Util Macros
#include <sstream>
#include <iomanip>

#define DEBUG_MILLISECONDS(title, time, nb) \
(bgfx::dbgTextPrintf(0, nb, ((0x2 + nb) << 4) | 0xF, \
(std::stringstream() << title \
<< std::fixed << std::setprecision(3) \
<< time << " ms").str().c_str()))

#define DEBUG_NUMBER(title, number, nb) \
(bgfx::dbgTextPrintf(0, nb, ((0x2 + nb) << 4) | 0xF, \
(std::stringstream() << title \
<< number).str().c_str()))

#endif // !PESTO_HPP
