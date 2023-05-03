#ifndef PESTO_SERVER_HPP
#define PESTO_SERVER_HPP

namespace pesto
{
    struct Application;

    class Server
    {
      public:
        explicit Server(Application *app) { this->app = app; }
      protected:
        Application *app;
    };
}

#endif // PESTO_SERVER_HPP
