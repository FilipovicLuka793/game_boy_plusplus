#ifndef _EMULATOR_H_
#define _EMULATOR_H_

#include "bus.h"
#include "cartridge.h"
#include "cpu.h"
#include "ram.h"
#include <cstdint>

class Emulator {
    private:

    Cartridge cart;
    Cpu cpu;
    Bus bus;
    Ram ram;

    public:

    Emulator(): bus(cart, ram), cpu(bus, ram) {}

    bool emu_init(char* path);

};

#endif