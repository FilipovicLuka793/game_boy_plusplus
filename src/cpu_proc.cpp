
#include <cstdint>
#include <cstdio>
#include "../inc/cpu.h" 



void Cpu::proc_nop(){

}

void Cpu::proc_stop(){
    printf("STOPED!!!");
    exit(-10);
}

void Cpu::proc_jp(){
    this->go_to_addr(this->fetched_data, false);
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

void Cpu::proc_cp(){
    int val = (int)this->a - (int)this->fetched_data;
    set_flags(val == 0, 1, ((int)this->a & 0x0F) - ((int)this->fetched_data & 0x0F ), val < 0);
}

void Cpu::proc_inc(){
    uint16_t val = read_reg(this->cur_instruction->reg_1) + 1;

    if(this->cur_instruction->reg_1 >= RT_AF){
        emu_cycles(1);
    }

    if(this->cur_instruction->reg_1 == RT_HL && this->cur_instruction->addr_type == AT_MR){
        val = this->bus.bus_read(read_reg(RT_HL)) + 1;
        val &= 0xFF;
        this->bus.bus_write(read_reg(RT_HL), val);
    }
    else {
        set_reg(this->cur_instruction->reg_1, val);
        val = read_reg(this->cur_instruction->reg_1);
    }

    if (this->cur_opcode == 0x03 ||
        this->cur_opcode == 0x13 ||
        this->cur_opcode == 0x23 ||
        this->cur_opcode == 0x33){
            return;
        }

    set_flags(val == 0, 0, (val & 0x0F) == 0, -1);
}

void Cpu::proc_dec(){
    uint16_t val = read_reg(this->cur_instruction->reg_1) - 1;

    if(this->cur_instruction->reg_1 >= RT_AF){
        emu_cycles(1);
    }

    if(this->cur_instruction->reg_1 == RT_HL && this->cur_instruction->addr_type == AT_MR){
        val = this->bus.bus_read(read_reg(RT_HL)) - 1;
        this->bus.bus_write(read_reg(RT_HL), val);
    }
    else {
        set_reg(this->cur_instruction->reg_1, val);
        val = read_reg(this->cur_instruction->reg_1);
    }

    if (this->cur_opcode == 0x0B ||
        this->cur_opcode == 0x1B ||
        this->cur_opcode == 0x2B ||
        this->cur_opcode == 0x3B){
            return;
        }

    set_flags(val == 0, 1, (val & 0x0F) == 0x0F, -1);
}

void Cpu::proc_jr(){
    int8_t val = (int8_t)(this->fetched_data & 0xFF);
    uint16_t addr = this->pc + val;
    go_to_addr(addr, false);
}

void Cpu::proc_di(){
    this->int_master_enable = false;
}

void Cpu::proc_ei(){
    this->int_master_enable = true;
}

void Cpu::proc_ldh(){
    if(!this->destination_is_memory){
        set_reg(this->cur_instruction->reg_1, this->bus.bus_read(this->fetched_data | 0xFF00));
    }
    else{
        this->bus.bus_write(this->mem_destionation, this->a);
    }
    emu_cycles(1);
}

void Cpu::proc_rlca(){
    uint8_t tmp = this->a;
    bool c = (tmp >> 7) & 1;
    tmp = (tmp << 1) | c;
    set_flags(0, 0, 0, c);
}

void Cpu::proc_rla(){
    uint8_t tmp = this->a;
    bool c = (tmp >> 7) & 1;
    tmp = (tmp << 1) | this->f.get_carry();
    set_flags(0, 0, 0, c);
}

void Cpu::proc_scf(){
    set_flags(-1, 0, 0, 1);
}

void Cpu::proc_ccf(){
    set_flags(-1, 0, 0, this->f.get_carry() ^ 1);
}

void Cpu::proc_cpl(){
    this->a = ~this->a;
    set_flags(-1, 1, 1, -1);
}

void Cpu::proc_rrca(){
    uint8_t tmp = this->a;
    bool c = tmp & 1;
    tmp = (tmp >> 1) | (c << 7);
    set_flags(0, 0, 0, c);
}

void Cpu::proc_rra(){
    uint8_t tmp = this->a;
    bool c = tmp & 1;
    tmp = (tmp >> 1) | (this->f.get_carry() << 7);
    set_flags(0, 0, 0, c);
}

void Cpu::proc_call(){
    
}