#include "../inc/cpu.h"
#include <cstdint>
#include <cstdio>
#include <cstdlib>

void Cpu::cpu_init(){
    this->pc = 0x100;
    this->a = 0x1;
}

void Cpu::fetch_instruction(){
    this->cur_opcode = bus.bus_read(this->pc++);
    this->cur_instruction = instruction_by_opcode(this->cur_opcode);
}

void Cpu::fetch_data(){
    this->mem_destionation = 0;
    this->destination_is_memory = false;

    switch (this->cur_instruction->addr_type) {
        case AT_NO:
            return;
        
        case AT_R_D8:{
            this->fetched_data = bus.bus_read(this->pc);
            emu_cycles(1);
            this->pc++;
            return;
        }

        case AT_R_D16:
        case AT_IMM16: {
            uint16_t lo = bus.bus_read(this->pc);
            emu_cycles(1);
            uint16_t hi = bus.bus_read(this->pc + 1);
            emu_cycles(1);
            this->fetched_data = (hi << 8) | lo;
            this->pc += 2;
            return;
        }

        case AT_R_MR: {
            uint16_t addr = this->read_reg(this->cur_instruction->reg_2);
            if(this->cur_instruction->reg_2 == RT_C){
                addr |= 0xFF00;
            }
            this->fetched_data = this->bus.bus_read(addr);
            emu_cycles(1);
            return;
        }

        case AT_R_HLI: {
            uint16_t addr = this->read_reg(this->cur_instruction->reg_2);
            this->fetched_data = this->bus.bus_read(addr);
            emu_cycles(1);
            this->set_reg(RT_HL, this->read_reg(RT_HL) + 1);
            return;
        }

        case AT_R_HLD: {
            uint16_t addr = this->read_reg(this->cur_instruction->reg_2);
            this->fetched_data = this->bus.bus_read(addr);
            emu_cycles(1);
            this->set_reg(RT_HL, this->read_reg(RT_HL) - 1);
            return;
        }

        case AT_MR_R: {
            this->fetched_data = this->read_reg(this->cur_instruction->reg_2);
            this->mem_destionation = this->read_reg(this->cur_instruction->reg_1);
            this->destination_is_memory = true;
            if(this->cur_instruction->reg_1 == RT_C){
                this->mem_destionation |= 0xFF00;
            }
            return;
        }

        case AT_MR_D8: {
            this->fetched_data = this->bus.bus_read(this->pc);
            emu_cycles(1);
            this->pc++;
            this->mem_destionation = this->read_reg(this->cur_instruction->reg_1);
            this->destination_is_memory = true;
            return;
        }

        case AT_R_R: {
            this->fetched_data = this->read_reg(this->cur_instruction->reg_2);
            return;
        }

        case AT_R: {
            this->fetched_data = this->read_reg(this->cur_instruction->reg_1);
            return;
        }

        case AT_HLD_R: {
            this->fetched_data = this->read_reg(this->cur_instruction->reg_2);
            this->mem_destionation = this->read_reg(this->cur_instruction->reg_1);
            this->destination_is_memory = true;
            this->set_reg(RT_HL, this->read_reg(RT_HL) - 1);
            return;
        }

        case AT_HLI_R: {
            this->fetched_data = this->read_reg(this->cur_instruction->reg_2);
            this->mem_destionation = this->read_reg(this->cur_instruction->reg_1);
            this->destination_is_memory = true;
            this->set_reg(RT_HL, this->read_reg(RT_HL) + 1);
            return;
        }

        case AT_D16_R:
        case AT_A16_R: {
            uint16_t lo = this->bus.bus_read(this->pc);
            emu_cycles(1);
            uint16_t hi = this->bus.bus_read(this->pc + 1);
            emu_cycles(1);
            this->mem_destionation = (hi << 8) | lo;
            this->destination_is_memory = true;
            this->pc += 2;
            this->fetched_data = this->read_reg(this->cur_instruction->reg_2);
            return;
        }

        case AT_R_A16: {
            uint16_t lo = this->bus.bus_read(this->pc);
            emu_cycles(1);
            uint16_t hi = this->bus.bus_read(this->pc + 1);
            emu_cycles(1);
            uint16_t addr = (hi << 8) | lo;
            this->pc += 2;
            this->fetched_data = this->bus.bus_read(addr);
            emu_cycles(1);
            return;
        }

        case AT_HL_SPR: {
            this->fetched_data = this->bus.bus_read(this->pc);
            emu_cycles(1);
            this->pc++;
            return;
        }

        case AT_D8: {
            this->fetched_data = this->bus.bus_read(this->pc);
            emu_cycles(1);
            this->pc++;
            return;
        }

        case AT_A8_R: {
            this->mem_destionation = this->bus.bus_read(this->pc) | 0xFF00;
            this->destination_is_memory = true;
            emu_cycles(1);
            this->pc++;
            return;
        }

        case AT_R_A8: {
            this->fetched_data = this->bus.bus_read(this->pc);
            emu_cycles(1);
            this->pc++;
            return;
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
        case IT_LD:
            proc_ld();
            return;
        case IT_XOR:
            proc_xor();
            return;
        case IT_AND:
            proc_and();
            return;
        case IT_OR:
            proc_or();
            return;
        case IT_INC:
            proc_inc();
            return;
        case IT_JR:
            proc_jr();
            return;
        case IT_DI:
            proc_di();
            return;
        case IT_LDH:
            proc_ldh();
            return;
        default:
            printf("Unknown instruction in execute: %02X\n", this->cur_opcode);
            exit(-7);
    }
}

bool Cpu::cpu_step(){
    uint16_t pc = this->pc;

    fetch_instruction();
    fetch_data();

    printf("%04X: %-6s %-8s %-3s %-3s (%02X, %02X, %02X)\t A: %02X\t B: %02X\t C: %02X\t D: %02X\t E: %02X\t H: %02X\t L: %02X\t FLAGS: Z: %d N: %d H: %d C: %d\n", 
        pc, 
        instruction_name(this->cur_instruction->ins_type).c_str(),
        addresing_name(this->cur_instruction->addr_type).c_str(),
        register_name(this->cur_instruction->reg_1).c_str(),
        register_name(this->cur_instruction->reg_2).c_str(),
        this->cur_opcode, this->bus.bus_read(pc + 1), this->bus.bus_read(pc + 2), 
        this->a, this->b, this->c, this->d, this->e, this->h, this->l,
        this->f.get_zero(), this->f.get_subtraction(), this->f.get_half_carry(), this->f.get_carry());

    execute();
    return true;
}

void Cpu::emu_cycles(int count){

}
