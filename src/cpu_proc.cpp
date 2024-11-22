
#include <cstdint>
#include <cstdio>
#include "../inc/cpu.h" 



void Cpu::proc_nop(){

}

void Cpu::proc_jp(){
    //TODO: implement conditions
    this->pc = this->fetched_data;
    emu_cycles(1);
}

void Cpu::proc_ld(){
    if(this->destination_is_memory){
        if(this->cur_instruction->reg_1 >= RT_AF){
            this->emu_cycles(1);
            this->bus.bus_write16(this->mem_destionation, this->fetched_data);
        } else{
            this->bus.bus_write(this->mem_destionation, this->fetched_data);
        }
        emu_cycles(1);
        return;
    }

    if(this->cur_instruction->addr_type == AT_HL_SPR){
        int8_t h = (this->read_reg(this->cur_instruction->reg_2) & 0xF) + (this->fetched_data & 0xF) >= 0x10;
        int8_t c = (this->read_reg(this->cur_instruction->reg_2) & 0xFF) + (this->fetched_data & 0xFF) >= 0x100;
        this->set_flags(0, 0, h, c);
        this->set_reg(this->cur_instruction->reg_1, this->read_reg(this->cur_instruction->reg_2) + (int8_t)this->fetched_data);
        return;
    }

    this->set_reg(this->cur_instruction->reg_1, this->fetched_data);
}

void Cpu::proc_xor(){
    this->fetched_data ^= this->fetched_data;
    this->set_reg(RT_A, this->fetched_data);
    set_flags(this->a == 0, 0, 0, 0);
}

void Cpu::proc_and(){
    this->fetched_data &= this->fetched_data;
    this->set_reg(RT_A, this->fetched_data);
    set_flags(this->a == 0, 0, 1, 0);
}

void Cpu::proc_or(){
    this->fetched_data |= this->fetched_data;
    this->set_reg(RT_A, this->fetched_data);
    set_flags(this->a == 0, 0, 0, 0);
}

void Cpu::proc_inc(){
    uint16_t val = read_reg(this->cur_instruction->reg_1) + 1;

    set_reg(this->cur_instruction->reg_1, val);
    val = read_reg(this->cur_instruction->reg_1);

    set_flags(val == 0, 0, (val & 0x0F) == 0, -1);
}

void Cpu::proc_dec(){
    uint16_t val = read_reg(this->cur_instruction->reg_1) - 1;

    set_reg(this->cur_instruction->reg_1, val);
    val = read_reg(this->cur_instruction->reg_1);

    set_flags(val == 0, 1, (val & 0x0F) == 0x0F, -1);
}

void Cpu::proc_jr(){
    int8_t val = (int8_t)(this->fetched_data & 0xFF);
    uint16_t addr = this->pc + val;
    go_to_addr(addr, false);
}