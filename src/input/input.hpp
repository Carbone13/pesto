#ifndef PESTO_INPUT_HPP
#define PESTO_INPUT_HPP

namespace pesto
{
    struct Application;

    struct Input
    {
        Application *app;

        bool keyPressed(int key);
        int getAxis(int keyA, int keyB);

        Input(Application *mainApp);
    };
}

#endif //PESTO_INPUT_HPP
