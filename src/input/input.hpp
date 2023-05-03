#ifndef PESTO_INPUT_HPP
#define PESTO_INPUT_HPP

namespace pesto
{
    struct Input : Server
    {
        bool keyPressed(int key);
        int getAxis(int keyA, int keyB);

        explicit Input(Application *app);
    };
}

#endif //PESTO_INPUT_HPP
