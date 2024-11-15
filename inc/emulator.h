#ifndef _EMULATOR_H_
#define _EMULATOR_H_

#include "cartridge.h"

class Emulator {
    private:

    Cartridge cart;

    public:

    Emulator() {}

    bool read_cart(char* path);

};

#endif