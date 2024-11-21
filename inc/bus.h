#ifndef _BUS_H_
#define _BUS_H_

#include "cartridge.h"
#include "ram.h"
#include <cstdint>
class Bus {
    private:

    Cartridge& cart;
    Ram& ram;

    public:

    Bus(Cartridge& cart, Ram& ram): cart(cart), ram(ram) {}

    uint8_t bus_read(uint16_t addr);
    void bus_write(uint16_t addr, uint8_t val);

    uint16_t bus_read16(uint16_t addr);
    void bus_write16(uint16_t addr, uint16_t val);

};

#endif