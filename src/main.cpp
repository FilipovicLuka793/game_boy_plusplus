#include <cstdio>
#include "../inc/emulator.h"

int main(int argc, char* argv[]){
    
    if(argc < 2) {
        printf("Path is not given.\n");
        return 1; 
    }

    Emulator emu;
    if(!emu.emu_init(argv[1])){
        printf("Emulator has stoped working!!!\n");
        return -1;
    }
    
    return 0;
}
