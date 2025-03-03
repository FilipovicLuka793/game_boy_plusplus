#include "../inc/timer.h"
#include <cstdint>
#include <cstdlib>

void Timer::timer_init(){
    this->div = 0xABCC;
}

uint8_t Timer::timer_read(uint16_t addr){
    switch (addr) {
        case 0xFF04:
            return this->div >> 8;
        case 0xFF05:
            return this->tima;
        case 0xFF06:
            return this->tma;
        case 0xFF07:
            return this->tac;
    }
    exit(-1);
}

void Timer::timer_write(uint16_t addr, uint8_t val){
    switch (addr) {
        case 0xFF04:
            this->div = 0;
            break;
        case 0xFF05:
            this->tima = val;
            break;
        case 0xFF06:
            this->tma = val;
            break;
        case 0xFF07:
            this->tac = val;
            break;
    }
}

void Timer::timer_tick(){
    uint16_t prev_div = this->div;

    this->div++;

    bool timer_update = false;

    switch (this->tac & (0b11)) {
        case 0b00:
            timer_update = (prev_div & (1 << 9)) && (!(div & (1 << 9)));
            break;
        case 0b01:
            timer_update = (prev_div & (1 << 3)) && (!(div & (1 << 3)));
            break;
        case 0b10:
            timer_update = (prev_div & (1 << 5)) && (!(div & (1 << 5)));
            break;
        case 0b11:
            timer_update = (prev_div & (1 << 7)) && (!(div & (1 << 7)));
            break;
    }

    if(timer_update && tac & (1 << 2)) {
        tima++;

        if(tima == 0xFF) {
            tima = tma;
            cpu.request_interrupt(Cpu::IT_TIMER);
        }
    }
}