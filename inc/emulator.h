#ifndef _EMULATOR_H_
#define _EMULATOR_H_

#include "bus.h"
#include "cartridge.h"
#include "cpu.h"
#include <cstdint>

class Emulator {
    private:

    Cartridge cart;
    Cpu cpu;
    Bus bus;

    public:

    Emulator(): bus(cart), cpu(bus) {}

    bool emu_init(char* path);

};

#endif