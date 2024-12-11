#ifndef _CPU_H_
#define _CPU_H_

#include "bus.h"
#include "flag_reg.h"
#include "instructions.h"
#include "ram.h"
#include <cstdint>
#include <functional>

class Cpu {
    
    private:

    Bus& bus;
    Ram& ram;

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

    bool int_master_enable;

    void fetch_instruction();
    void fetch_data();
    void execute();

    void emu_cycles(int count);

    uint16_t read_reg(register_type rt);
    void set_reg(register_type tr, uint16_t val);

    //Instruction processes
    void set_flags(int8_t z, int8_t n, int8_t h, int8_t c);
    void go_to_addr(uint16_t addr, bool pc_push);
    bool check_con();

    void proc_nop();
    void proc_jp();
    void proc_dec();
    void proc_ld();
    void proc_inc();
    void proc_rlca();
    void proc_add();
    void proc_rrca();
    void proc_stop();
    void proc_rla();
    void proc_jr();
    void proc_rra();
    void proc_daa();
    void proc_cpl();
    void proc_scf();
    void proc_ccf();
    void proc_halt();
    void proc_adc();
    void proc_sub();
    void proc_sbc();
    void proc_and();
    void proc_xor();
    void proc_or();
    void proc_cp();
    void proc_ret();
    void proc_pop();
    void proc_call();
    void proc_push();
    void proc_rst();
    void proc_prefix();
    void proc_reti();
    void proc_di();
    void proc_ei();
    void proc_rlc();
    void proc_rrc();
    void proc_rl();
    void proc_rr();
    void proc_sla();
    void proc_sra();
    void proc_swap();
    void proc_srl();
    void proc_bit();
    void proc_res();
    void proc_set();
    void proc_ldh();

    bool halted = false;

    public:

    Cpu(Bus& bus, Ram& ram): bus(bus), ram(ram) {}

    void cpu_init();
    bool cpu_step();

    uint8_t get_ie_register();

    void stack_push(uint8_t data);
    void stack_push16(uint16_t data);

    uint8_t stack_pop();
    uint16_t stack_pop16();

};

#endif