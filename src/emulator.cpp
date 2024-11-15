#include "../inc/emulator.h"
#include <cstdint>
#include <cstdio>
#include <cstdlib>

bool Emulator::emu_init(char* path){
    if(!cart.load_cart(path)) {
        printf("Failed to load cartridge.\n");
        return false; 
    }
    printf("Loading finished...\n");
    
    this->cpu.cpu_init();
    
    while(true){
        if(!this->cpu.cpu_step()){
            printf("CPU stopped\n");
            return false;
        }
    }

    return true;
}

uint8_t Emulator::bus_read(uint16_t addr){
    if(addr >= 0x0000 && addr < 0x8000){
        this->cart.read_cart(addr);
    }
    printf("Read not yet implemented\n");
    exit(-2);
}

void Emulator::bus_write(uint16_t addr, uint8_t val){
    printf("Write not yet implemented\n");
    exit(-3);
}