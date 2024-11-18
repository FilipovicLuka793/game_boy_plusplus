#include "../inc/cpu.h"
#include <cstdint>
#include <cstdio>
#include <cstdlib>

void Cpu::cpu_init(){
    this->pc = 0x100;
    this->a = 0x1;
}

void Cpu::fetch_instruction(){
    this->cur_opcode = bus.bus_read(this->pc);
    this->cur_instruction = instruction_by_opcode(this->cur_opcode);
}

void Cpu::fetch_data(){
    this->mem_destionation = 0;
    this->destination_is_memory = false;

    switch (this->cur_instruction->addr_type) {
        case AT_NO:
            return;
        
        case AT_IMM16: {
            uint16_t lo = bus.bus_read(this->pc);
            emu_cycles(1);
            uint16_t hi = bus.bus_read(this->pc + 1);
            emu_cycles(1);
            this->fetched_data = (hi << 8) | lo;
            this->pc += 2;
            return;
        }

        case AT_MEMR: {
            this->destination_is_memory = true;
            this->mem_destionation = this->read_reg(this->cur_instruction->reg_1);
        }
        default:
            printf("Unkonwn addresing type: %d (%02X)\n", this->cur_instruction->addr_type, this->cur_opcode);
            exit(-5);
            return;
    }
}

void Cpu::execute(){
    switch(this->cur_instruction->ins_type){
        case IT_NOP:
            proc_nop();
            return;
        case IT_JP:
            proc_jp();
            return;
        case IT_DEC:
            proc_dec();
            return;
        default:
            printf("Unknown instruction in execute: %d\n", this->cur_instruction->ins_type);
    }
}

bool Cpu::cpu_step(){

    fetch_instruction();
    fetch_data();

    printf("Opcode: %02X, Ins type: %d\n", this->cur_opcode, this->cur_instruction->ins_type);

    execute();
    this->pc++;
    return true;
}

void Cpu::emu_cycles(int count){

}
