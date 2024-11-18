#include "../inc/cpu.h"
#include <cstdint>

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