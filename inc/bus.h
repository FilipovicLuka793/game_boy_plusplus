#ifndef _BUS_H_
#define _BUS_H_

#include "cartridge.h"
#include <cstdint>
class Bus {
    private:

    Cartridge& cart;

    public:

    Bus(Cartridge& cart): cart(cart) {}

    uint8_t bus_read(uint16_t addr);
    void bus_write(uint16_t addr, uint8_t val);

};

#endif