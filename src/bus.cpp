#include "../inc/bus.h"
#include <cstdint>
#include <cstdio>
#include <cstdlib>

uint8_t Bus::io_read(uint16_t addr) {
  if (addr == 0xFF01) {
    return this->serial_data[0];
  } else if (addr == 0xFF02) {
    return this->serial_data[1];
  } else if (addr >= 0xFF04 && addr <= 0xFF07) {
    // TODO
    exit(-10);
  } else if (addr == 0xFF0F) {
    return this->int_flags;
  }

  printf("ERROR: UNSUPPORTED bus_read(%04X)\n", addr);
  return 0;
}

void Bus::io_write(uint16_t addr, uint8_t val) {
  if (addr == 0xFF01) {
    serial_data[0] = val;
    return;
  } else if (addr == 0xFF02) {
    serial_data[1] = val;
    return;
  } else if (addr >= 0xFF04 && addr <= 0xFF07) {
    // TODO
    exit(-10);
  } else if (addr == 0xFF0F) {
    this->int_flags = val;
    return;
  }
  printf("ERROR: UNSUPPORTED bus_write(%04X)\n", addr);
}

uint8_t Bus::bus_read(uint16_t addr) {
  if (addr < 0x8000) {
    // ROM
    return this->cart.read_cart(addr);
  } else if (addr < 0xA000) {
    // CHR RAM
    printf("Read not yet implemented: %04X\n", addr);
    return 0;
  } else if (addr < 0xC000) {
    // Cartridge RAM
    printf("Read not yet implemented: %04X\n", addr);
    return 0;
  } else if (addr < 0xE000) {
    // WRAM
    return this->ram.wram_read(addr);
  } else if (addr < 0xFE00) {
    // RESERVED!!!
    return 0;
  } else if (addr < 0xFEA0) {
    // OAM
    printf("Read not yet implemented: %04X\n", addr);
    return 0;
  } else if (addr < 0xFF00) {
    // RESERVED!!!
    return 0;
  } else if (addr < 0xFF80) {
    // I/O registers
    return this->io_read(addr);
  } else if (addr == 0xFFFF) {
    // IE register
    return get_ie_reg();
  }

  return this->ram.hram_read(addr);
}

void Bus::bus_write(uint16_t addr, uint8_t val) {
  if (addr < 0x8000) {
    this->cart.write_cart(addr, val);
  } else if (addr < 0xA000) {
    // CHR RAM
    printf("Write not yet implemented: %04X\n", addr);
    // exit(-3);
  } else if (addr < 0xC000) {
    // Cartridge RAM
    printf("Write not yet implemented: %04X\n", addr);
    // exit(-3);
  } else if (addr < 0xE000) {
    // WRAM
    this->ram.wram_write(addr, val);
  } else if (addr < 0xFE00) {
    // RESERVED!!!
  } else if (addr < 0xFEA0) {
    // OAM
    printf("Write not yet implemented: %04X\n", addr);
    // exit(-3);
  } else if (addr < 0xFF00) {
    // RESERVED!!!
  } else if (addr < 0xFF80) {
    // I/O registers
    this->io_write(addr, val);
  } else if (addr == 0xFFFF) {
    // IE register
    set_ie_reg(val);
  } else {
    this->ram.hram_write(addr, val);
  }
}

uint16_t Bus::bus_read16(uint16_t addr) {
  uint16_t lo = bus_read(addr);
  uint16_t hi = bus_read(addr + 1);
  return (hi << 8) | lo;
}

void Bus::bus_write16(uint16_t addr, uint16_t val) {
  bus_write(addr + 1, (val >> 8) & 0xFF);
  bus_write(addr, val & 0xFF);
}

uint8_t Bus::get_ie_reg() { return this->ie_register; }

void Bus::set_ie_reg(uint8_t val) { this->ie_register = val; }

uint8_t Bus::get_int_flags() { return this->int_flags; }

void Bus::set_int_flags(uint8_t val) { this->int_flags = val; }
