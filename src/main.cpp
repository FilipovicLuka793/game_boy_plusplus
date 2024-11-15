#include <cstdio>
#include "../inc/emulator.h"

int main(int argc, char* argv[]){
    
    if(argc < 2) {
        printf("Path is not given.\n");
        return 1; 
    }

    Emulator emu;

    if(!emu.read_cart(argv[1])) {
        printf("Failed to load cartridge.\n");
        return 1; 
    }

    printf("Loading finished...\n");
    
    return 0;
}
