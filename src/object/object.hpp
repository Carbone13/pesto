#ifndef PESTO_OBJECT_HPP
#define PESTO_OBJECT_HPP

#include <glm/glm.hpp>
using namespace glm;

namespace pesto
{
    struct Application;

    class Object
    {
      public:
        explicit Object(Application *app) { this->app = app; }

        vec2 position{0.0f, 0.0f};
        vec2 scale {1.0f};
        float rotation {0.0f};

      protected:
        Application *app;
    };
}
#endif // PESTO_OBJECT_HPP
