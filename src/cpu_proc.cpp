
#include <cstdio>
#include "../inc/cpu.h" 

void Cpu::proc_nop(){

}

void Cpu::proc_jp(){
    this->pc = this->fetched_data;
    emu_cycles(1);
}

void Cpu::proc_dec(){
    
}
