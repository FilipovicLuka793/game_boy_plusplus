
#include <cstdio>
#include "../inc/cpu.h" 



void Cpu::proc_nop(){

}

void Cpu::proc_jp(){
    //TODO: implement conditions
    this->pc = this->fetched_data;
    emu_cycles(1);
}

void Cpu::proc_dec(){
    //TODO
}

void Cpu::proc_ld(){
    if(this->destination_is_memory){
        if(this->cur_instruction->reg_1 >= RT_AF){
            this->emu_cycles(1);
            this->bus.bus_write16(this->mem_destionation, this->fetched_data);
        } else{
            this->bus.bus_write(this->mem_destionation, this->fetched_data);
        }
    }

    this->set_reg(this->cur_instruction->reg_1, this->fetched_data);
}

void Cpu::proc_xor(){
    this->fetched_data ^= this->fetched_data;
    this->set_reg(RT_A, this->fetched_data);
    set_flags(this->a == 0, 0, 0, 0);
}
