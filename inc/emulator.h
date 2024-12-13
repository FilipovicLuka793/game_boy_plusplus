#ifndef _EMULATOR_H_
#define _EMULATOR_H_

#include "bus.h"
#include "cartridge.h"
#include "cpu.h"
#include "ram.h"
#include "ui.h"
#include <cstdint>
#include <type_traits>

class Emulator {
    private:

    Cartridge cart;
    Cpu cpu;
    Bus bus;
    Ram ram;
    uint64_t ticks;
    Ui ui;
    
    bool die = false;

    

    public:

    Emulator(): bus(cart, ram), cpu(bus, ram, &ticks), ui(&die) {}

    void* cpu_run(void* p);
    bool emu_init(char* path);

};

#endif