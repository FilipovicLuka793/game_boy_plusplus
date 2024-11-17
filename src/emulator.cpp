#include "../inc/emulator.h"
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
