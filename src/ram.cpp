#include "../inc/ram.h"
#include <cstdint>
#include <cstdio>

uint8_t Ram::wram_read(uint16_t addr) {
  addr -= 0xC000;
  return this->wram[addr];
}

void Ram::wram_write(uint16_t addr, uint8_t val) {
  addr -= 0xC000;
  this->wram[addr] = val;
}

uint8_t Ram::hram_read(uint16_t addr) {
  addr -= 0xFF80;
  return this->hram[addr];
}

void Ram::hram_write(uint16_t addr, uint8_t val) {
  addr -= 0xFF80;
  this->hram[addr] = val;
}
