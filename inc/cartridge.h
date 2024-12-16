#ifndef _CARTRIDGE_H_
#define _CARTRIDGE_H_

#include <cstdint>
#include <string>
#include <unordered_map>

typedef struct {
  uint8_t entry_point[4];
  uint8_t nintendo_logo[0x30];
  char title[16];
  uint16_t new_licensee_code;
  uint8_t sgb_flag;
  uint8_t catrige_type;
  uint8_t rom_size;
  uint8_t ram_size;
  uint8_t destination_code;
  uint8_t old_licensee_code;
  uint8_t maks_rom_version_number;
  uint8_t header_checksum;
  uint16_t global_checksum;
} rom_header;

class Cartridge {

private:
  std::string filename = "";
  uint32_t rom_size = 0;
  uint8_t *rom_data;
  rom_header *header;

public:
  bool load_cart(char *path);
  uint8_t read_cart(uint16_t addr);
  void write_cart(uint16_t addr, uint8_t val);
};

#endif
