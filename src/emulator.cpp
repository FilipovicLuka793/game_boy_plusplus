#include "../inc/emulator.h"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>

static void* cpu_run_wrapper(void* p) {
    Emulator* emulator = static_cast<Emulator*>(p);
    return emulator->cpu_run(p); 
}

void* Emulator::cpu_run(void* p){
    this->cpu.cpu_init();
    this->ticks = 0;
    
    while(true){
        if(!this->cpu.cpu_step()){
            printf("CPU stopped\n");
            return 0;
        }
        this->ticks++;
    }

    return 0;
}

bool Emulator::emu_init(char* path){
    if(!cart.load_cart(path)) {
        printf("Failed to load cartridge.\n");
        return false; 
    }
    printf("Loading finished...\n");
    
    this->ui.ui_init();

    pthread_t t1;

    if(pthread_create(&t1, NULL, cpu_run_wrapper, this)){
        printf("FILED TO START CPU THREAD!\n");
        return -1;
    }

    while(!this->die){
        usleep(1000);
        this->ui.ui_handle_events();
    }

    return true;
}
