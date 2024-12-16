#ifndef _BUS_H_
#define _BUS_H_

#include "cartridge.h"
#include "ram.h"
#include <cstdint>
#include <vector>
class Bus {
private:
  Cartridge &cart;
  Ram &ram;

  uint8_t ie_register;

  char serial_data[2];

  uint8_t int_flags;

  uint8_t io_read(uint16_t addr);
  void io_write(uint16_t addr, uint8_t val);

public:
  Bus(Cartridge &cart, Ram &ram) : cart(cart), ram(ram) {}

  uint8_t bus_read(uint16_t addr);
  void bus_write(uint16_t addr, uint8_t val);

  uint16_t bus_read16(uint16_t addr);
  void bus_write16(uint16_t addr, uint16_t val);

  uint8_t get_ie_reg();
  void set_ie_reg(uint8_t val);

  uint8_t get_int_flags();
  void set_int_flags(uint8_t val);
};

#endif
