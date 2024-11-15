#include "../inc/cpu.h"

void Cpu::cpu_init(){
    this->pc = 0x100;
}

bool Cpu::cpu_step(){
    return true;
}