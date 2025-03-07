#ifndef _EMULATOR_H_
#define _EMULATOR_H_

#include "bus.h"
#include "cartridge.h"
#include "cpu.h"
#include "ram.h"
#include "timer.h"
#include "ui.h"
#include <cstdint>
#include <type_traits>

class Emulator {
    private:

    friend class Cpu;

    Cartridge cart;
    Cpu cpu;
    Bus bus;
    Ram ram;
    uint64_t ticks;
    Ui ui;
    Timer timer;
    
    bool die = false;

    void emu_cycles(int cpu_cycles);

    public:

    Emulator(): bus(cart, ram, timer), cpu(bus, ram, &ticks, [this](int x) {this->emu_cycles(x);}), ui(&die), timer(cpu) {}

    void* cpu_run(void* p);
    bool emu_init(char* path);

};

#endif