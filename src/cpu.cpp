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
            return;;

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
        default:
            printf("Unknown instruction in execute: %d\n", this->cur_instruction->ins_type);
    }
}

bool Cpu::cpu_step(){

    uint16_t pc = this->pc;
    fetch_instruction();
    fetch_data();

    printf("Opcode: %02X, Ins type: %d\n", this->cur_opcode, this->cur_instruction->ins_type);

    execute();
    this->pc++;
    return true;
}
