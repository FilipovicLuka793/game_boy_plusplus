#include "../inc/cpu.h"
#include <cstdint>

void Cpu::stack_push(uint8_t data) {
  this->sp--;
  this->bus.bus_write(this->sp, data);
}

void Cpu::stack_push16(uint16_t data) {
  stack_push((data >> 8) & 0xFF);
  stack_push(data & 0xFF);
}

uint8_t Cpu::stack_pop() { return this->bus.bus_read(this->sp++); }

uint16_t Cpu::stack_pop16() {
  uint16_t lo = stack_pop();
  uint16_t hi = stack_pop();

  return (hi << 8) | lo;
}
