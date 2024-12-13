#include "../inc/bus.h"
#include <cstdint>
#include <cstdio>

uint8_t Bus::bus_read(uint16_t addr){
    if(addr < 0x8000){
        //ROM
        return this->cart.read_cart(addr);
    }
    else if(addr < 0xA000){
        //CHR RAM
        printf("Read not yet implemented: %04X\n", addr);
        return 0;
    }
    else if(addr < 0xC000){
        //Cartridge RAM
        printf("Read not yet implemented: %04X\n", addr);
        return 0;
    }
    else if(addr < 0xE000){
        //WRAM
        return this->ram.wram_read(addr);
    }
    else if(addr < 0xFE00){
        //RESERVED!!!
        return 0;
    }
    else if(addr < 0xFEA0) {
        //OAM
        printf("Read not yet implemented: %04X\n", addr);
        return 0;
    }
    else if(addr < 0xFF00) {
        //RESERVED!!!
        return 0;
    }
    else if(addr < 0xFF80) {
        //I/O registers
        printf("Read not yet implemented: %04X\n", addr);
        return 0x91;
    }
    else if(addr == 0xFFFF) {
        //IE register
        return get_ie_reg();
    }

    return this->ram.hram_read(addr);
}

void Bus::bus_write(uint16_t addr, uint8_t val){
    if(addr < 0x8000){
        this->cart.write_cart(addr, val);
    }
    else if(addr < 0xA000){
        //CHR RAM
        printf("Write not yet implemented: %04X\n", addr);
        //exit(-3);
    }
    else if(addr < 0xC000){
        //Cartridge RAM
        printf("Write not yet implemented: %04X\n", addr);
        //exit(-3);
    }
    else if(addr < 0xE000){
        //WRAM
        this->ram.wram_write(addr, val);
    }
    else if(addr < 0xFE00){
        //RESERVED!!!
    }
    else if(addr < 0xFEA0) {
        //OAM
        printf("Write not yet implemented: %04X\n", addr);
        //exit(-3);
    }
    else if(addr < 0xFF00) {
        //RESERVED!!!
    }
    else if(addr < 0xFF80) {
        //I/O registers
        printf("Write not yet implemented: %04X\n", addr);
        //exit(-3);
    }
    else if(addr == 0xFFFF) {
        //IE register
        set_ie_reg(val);
    }
    else{
        this->ram.hram_write(addr, val);
    }
    
}

uint16_t Bus::bus_read16(uint16_t addr){
    uint16_t lo = bus_read(addr);
    uint16_t hi = bus_read(addr + 1);
    return (hi << 8) | lo;
}

void Bus::bus_write16(uint16_t addr, uint16_t val){
    bus_write(addr + 1, (val >> 8) & 0xFF);
    bus_write(addr, val & 0xFF);
}

uint8_t Bus::get_ie_reg(){
    return this->ie_register;
}

void Bus::set_ie_reg(uint8_t val){
    this->ie_register = val;
}