#ifndef PESTO_SERVER_HPP
#define PESTO_SERVER_HPP

namespace pesto
{
    struct Application;

    class Server
    {
      public:
        Server() = default;
        explicit Server(Application *app) { this->app = app; }

      protected:
        Application *app {nullptr};
    };
}

#endif // PESTO_SERVER_HPP
