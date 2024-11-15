#ifndef _CPU_H_
#define _CPU_H_

#include "flag_reg.h"
#include <cstdint>

class Cpu {
    
    private:

    uint8_t a; // Accumulator
    Flag_reg f; // Flags
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    uint8_t h;
    uint8_t l;
    uint16_t sp;
    uint16_t pc;

    public:

    void cpu_init();
    bool cpu_step();

};

#endif