#ifndef _CPU_H_
#define _CPU_H_

#include "bus.h"
#include "flag_reg.h"
#include "instructions.h"
#include <cstdint>
#include <functional>

class Cpu {
    
    private:

    Bus& bus;

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

    uint16_t fetched_data;
    uint16_t mem_destionation;
    bool destination_is_memory;
    uint8_t cur_opcode;
    instruction* cur_instruction;

    void fetch_instruction();
    void fetch_data();
    void execute();

    void emu_cycles(int count);

    uint16_t read_reg(register_type rt);

    //Instruction processes
    void proc_nop();
    void proc_jp();
    void proc_dec();

    public:

    Cpu(Bus& bus): bus(bus) {}

    void cpu_init();
    bool cpu_step();

    

};

#endif