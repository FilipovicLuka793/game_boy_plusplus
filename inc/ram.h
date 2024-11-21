#ifndef _RAM_H_
#define _RAM_H_

#include <cstdint>
class Ram {

    private:

    uint8_t wram[0x2000];
    uint8_t hram[0x80];
    
    public:

    uint8_t wram_read(uint16_t addr);
    void wram_write(uint16_t addr, uint8_t val);

    uint8_t hram_read(uint16_t addr);
    void hram_write(uint16_t addr, uint8_t val);

};

#endif