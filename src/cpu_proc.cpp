
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
    this->go_to_addr(this->fetched_data, true);
}

void Cpu::proc_pop(){
    uint16_t lo = stack_pop();
    emu_cycles(1);
    uint16_t hi = stack_pop();
    emu_cycles(1);

    uint16_t x = (hi << 8) | lo;
    set_reg(this->cur_instruction->reg_1, x);

    if(this->cur_instruction->reg_1 == RT_AF){
        set_reg(this->cur_instruction->reg_1, x & 0xFFF0);
    }
}

void Cpu::proc_push(){
    uint16_t hi = (read_reg(cur_instruction->reg_1) >> 8) & 0xFF;
    emu_cycles(1);
    stack_push(hi);

    uint16_t lo = read_reg(cur_instruction->reg_1) & 0xFF;
    emu_cycles(1);
    stack_push(lo);

    emu_cycles(1);
}

void Cpu::proc_ret(){
    if(this->cur_instruction->con_type != CT_NONE){
        emu_cycles(1);
    }

    if(check_con()){
        uint16_t lo = stack_pop();
        emu_cycles(1);
        uint16_t hi = stack_pop();
        emu_cycles(1);

        uint16_t x = (hi << 8) | lo;
        this->pc = x;
        emu_cycles(1);
    }
}

void Cpu::proc_reti(){
    this->int_master_enable = true;
    proc_ret();
}

void Cpu::proc_rst(){
    go_to_addr(this->cur_instruction->param, true);
}

void Cpu::proc_add(){
    uint32_t val;

    bool is_16bit = cur_instruction->reg_1 >= RT_AF;

    if(is_16bit) emu_cycles(1);

    if(cur_instruction->reg_1 == RT_SP){
        val = read_reg(cur_instruction->reg_1) + (int8_t)fetched_data;
    }
    else {
        val = read_reg(cur_instruction->reg_1) + fetched_data;
    }

    int8_t z = (val & 0xFF) == 0;
    int8_t h = (read_reg(cur_instruction->reg_1) & 0xF) + (fetched_data & 0xF) >= 0x10;
    int8_t c = (int)(read_reg(cur_instruction->reg_1) & 0xFF) + (int)(fetched_data & 0xFF) >= 0x100;

    if(is_16bit){
        z = -1;
        h = (read_reg(cur_instruction->reg_1) & 0xFFF) + (fetched_data & 0xFFF) >= 0x1000;
        c = (((uint32_t)read_reg(cur_instruction->reg_1)) + ((uint32_t)fetched_data)) >= 0x10000;
    }

    if(cur_instruction->reg_1 == RT_SP){
        z = 0;
        h = (read_reg(cur_instruction->reg_1) & 0xF) + (fetched_data & 0xF) >= 0x10;
        c = (int)(read_reg(cur_instruction->reg_1) & 0xFF) + (int)(fetched_data & 0xFF) >= 0x100;
    }

    set_reg(cur_instruction->reg_1, val & 0xFFFF);
    set_flags(z, 0, h, c);
}

void Cpu::proc_adc(){
    uint16_t fe = fetched_data;
    uint16_t ra = this->a;
    uint16_t c = this->f.get_carry();

    this->a = (ra + fe + c) & 0xFF;

    set_flags(this->a == 0, 0, (ra & 0xF) + (fe & 0xF) + c > 0xF, ra + fe + c > 0xFF);
}

void Cpu::proc_sub(){
    uint16_t val = read_reg(cur_instruction->reg_1) - fetched_data;

    int8_t z = val == 0;
    int8_t h = ((int)read_reg(cur_instruction->reg_1) & 0xF) - ((int)fetched_data & 0xF) < 0;
    int8_t c = ((int)read_reg(cur_instruction->reg_1)) - ((int)fetched_data) < 0;

    set_reg(cur_instruction->reg_1, val);
    set_flags(z, 1, h, c);
}

void Cpu::proc_sbc(){
    uint8_t ca = this->f.get_carry();
    uint8_t val = fetched_data + ca;

    int8_t z = read_reg(cur_instruction->reg_1) - val == 0;
    int8_t h = ((int)read_reg(cur_instruction->reg_1) & 0xF) - ((int)fetched_data & 0xF) - ((int)ca) < 0;
    int8_t c = ((int)read_reg(cur_instruction->reg_1)) - ((int)fetched_data) - ((int)ca) < 0;

    set_reg(cur_instruction->reg_1, read_reg(cur_instruction->reg_1) - val);
    set_flags(z, 1, h, c);
}

void Cpu::proc_halt(){
    this->halted = true;
}