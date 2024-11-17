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
    printf("Write not yet implemented\n");
    exit(-3);
}