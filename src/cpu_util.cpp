#include "../inc/cpu.h"
#include <cstdint>
#include <cstdio>
#include <cstdlib>

uint16_t Cpu::read_reg(register_type rt){
    switch (rt) {
        case RT_A : return this->a;
        case RT_F : return this->f.get_reg();
        case RT_B : return this->b;
        case RT_C : return this->c;
        case RT_D : return this->d;
        case RT_E : return this->e;
        case RT_H : return this->h;
        case RT_L : return this->l;

        case RT_AF : return (this->a << 8) | (this->f.get_reg() & 0x00FF);
        case RT_BC : return (this->b << 8) | (this->c & 0x00FF);
        case RT_DE : return (this->d << 8) | (this->e & 0x00FF);
        case RT_HL : return (this->h << 8) | (this->l & 0x00FF);

        case RT_PC : return this->pc;
        case RT_SP : return this->sp;
        default: return 0;
    }
}

void Cpu::set_reg(register_type rt, uint16_t val){
    switch (rt) {
        case RT_A : this->a = val; return;
        case RT_F : this->f.set_reg(val); return;
        case RT_B : this->b = val; return;
        case RT_C : this->c = val; return;
        case RT_D : this->d = val; return;
        case RT_E : this->e = val; return;
        case RT_H : this->h = val; return;
        case RT_L : this->l = val; return;

        case RT_AF : {
            this->a = val >> 8;
            this->f.set_reg(val);
            return;
        }
        case RT_BC : {
            this->b = val >> 8;
            this->c = val;
            return;
        }
        case RT_DE : {
            this->d = val >> 8;
            this->e = val;
            return;
        }
        case RT_HL : {
            this->h = val >> 8;
            this->l = val;
            return;
        }

        case RT_PC : this->pc = val; return;
        case RT_SP : this->sp = val; return;
        default: return;
    }
}

void Cpu::set_flags(int8_t z, int8_t n, int8_t h, int8_t c){
    if(z != -1){
        this->f.set_zero(z);
    }
    if(n != -1){
        this->f.set_subtraction(n);
    }
    if(h != -1){
        this->f.set_half_carry(h);
    }
    if(c != -1){
        this->f.set_carry(c);
    }
}

bool Cpu::check_con(){
    bool z = this->f.get_zero();
    bool c = this->f.get_carry();

    switch (this->cur_instruction->con_type) {
        case CT_NONE: return true;
        case CT_Z: return z;
        case CT_NZ: return !z;
        case CT_C: return c;
        case CT_NC: return !c;
    }
    return false;
}

void Cpu::go_to_addr(uint16_t addr, bool pc_push){
    if(check_con()){
        if(pc_push){
            emu_cycles(2);
            stack_push16(this->pc);
        }

        this->pc = addr;
        emu_cycles(1);
    }
}

uint8_t Cpu::read_reg_cb(register_type rt){
    switch (rt) {
        case RT_A: return this->a;
        case RT_B: return this->b;
        case RT_C: return this->c;
        case RT_D: return this->d;
        case RT_E: return this->e;
        case RT_H: return this->h;
        case RT_L: return this->l;
        case RT_HL: {
            return this->bus.bus_read(read_reg(RT_HL));
        }
        default: {
            printf("ERROR: INVALID CB REG: %d\n", rt);
            exit(-8);
        }
    }
}

void Cpu::set_reg_cb(register_type rt, uint8_t val){
    switch (rt) {
        case RT_A: this->a = val & 0xFF; break;
        case RT_B: this->b = val & 0xFF; break;;
        case RT_C: this->c = val & 0xFF; break;;
        case RT_D: this->d = val & 0xFF; break;;
        case RT_E: this->e = val & 0xFF; break;;
        case RT_H: this->h = val & 0xFF; break;;
        case RT_L: this->l = val & 0xFF; break;;
        case RT_HL: this->bus.bus_write(read_reg(RT_HL), val); break;
        default: {
            printf("ERROR: INVALID CB REG: %d\n", rt);
            exit(-8);
        }
    }
}

uint8_t Cpu::get_ie_register(){
    return this->bus.get_ie_reg();
}

