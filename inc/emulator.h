#ifndef _EMULATOR_H_
#define _EMULATOR_H_

#include "cartridge.h"
#include "cpu.h"
#include <cstdint>

class Emulator {
    private:

    Cartridge cart;
    Cpu cpu;

    uint8_t bus_read(uint16_t addr);
    void bus_write(uint16_t addr, uint8_t val);

    public:

    Emulator() {}

    bool emu_init(char* path);

};

#endif