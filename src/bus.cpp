#include "../inc/bus.h"
#include <cstdint>

uint8_t Bus::bus_read(uint16_t addr){
    if(addr >= 0x0000 && addr < 0x8000){
        return this->cart.read_cart(addr);
    }
    printf("Read not yet implemented\n");
    exit(-2);
}

void Bus::bus_write(uint16_t addr, uint8_t val){
    if(addr >= 0x0000 && addr < 0x8000){
        this->cart.write_cart(addr, val);
        return;
    }
    printf("Write not yet implemented\n");
    exit(-3);
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