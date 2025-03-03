#pragma once
#ifndef _TIMER_H_
#define _TIMER_H_

#include "cpu.h"
#include <cstdint>
class Timer {
    private:

    Cpu& cpu;

    uint16_t div;
    uint8_t tima;
    uint8_t tma;
    uint8_t tac;

    public:

    Timer(Cpu& cpu): cpu(cpu) {}

    void timer_init();
    void timer_tick();

    void timer_write(uint16_t addr, uint8_t val);
    uint8_t timer_read(uint16_t addr);



};

#endif