#include "../inc/cartridge.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <unordered_map>

std::unordered_map<uint8_t, std::string> old_licensee_code_map = {
    {0x00, "None"},
    {0x01, "Nintendo Research & Development 1"},
    {0x08, "Capcome"},
    {0x13, "EA(Electronic Arts)"},
    {0x18, "Hudson Soft"},
    {0x19, "B-AI"},
    {0x20, "KSS"},
    {0x22, "Planning Office WADA"},
    {0x24, "PCM Complete"},
    {0x25, "San-X"},
    {0x28, "Kemco"},
    {0x29, "SETA Corporation"},
    {0x30, "Viacom"},
    {0x31, "Nintendo"},
    {0x32, "Bandai"},
    {0x33, "Ocean Software/Acclaim Entertainment"},
    {0x34, "Konami"},
    {0x35, "HectorSoft"},
    {0x37, "Taito"},
    {0x38, "Hudson Soft"},
    {0x39, "Banpresto"},
    {0x41, "Ubi Soft"},
    {0x42, "Atlus"},
    {0x44, "Malibu Interactive"},
    {0x46, "Angel"},
    {0x47, "Bullet-Proof Software"},
    {0x49, "Irem"},
    {0x50, "Absolute"},
    {0x51, "Acclaim Entertainment"},
    {0x52, "Activision"},
    {0x53, "Sammy USA Corporation"},
    {0x54, "Konami"},
    {0x55, "Hi Tech Expressions"},
    {0x56, "LJN"},
    {0x57, "Matchbox"},
    {0x58, "Mattel"},
    {0x59, "Milton Bradley Company"},
    {0x60, "Titus Interative"},
    {0x61, "Virgin Games Ltd."},
    {0x64, "Lucasfilm Games"},
    {0x67, "Ocean Software"},
    {0x69, "EA (Electronic Arts)"},
    {0x70, "Infogrames"},
    {0x71, "Interplay Entertainment"},
    {0x72, "Broderbund"},
    {0x73, "Sculptured Software"},
    {0x75, "The Sales Curve Limited"},
    {0x78, "THQ"},
    {0x79, "Accolade"},
    {0x80, "Misawa Entertainment"},
    {0x83, "lozc"},
    {0x86, "Tokuma Shoten"},
    {0x87, "Tsukuda Original"},
    {0x91, "Chunsoft Co."},
    {0x92, "Video System"},
    {0x93, "Ocean Software/Acclaim Entertainment"},
    {0x95, "Varie"},
    {0x96, "Yonezawa/s'pal"},
    {0x97, "Kaneko"},
    {0x99, "Pack-In-Video"},
    {0xA4, "Konami (Yu-Gi-Oh!)"}
};

std::unordered_map<uint8_t, std::string> cartridge_type_map = {
    {0x00, "ROM ONLY"},
    {0x01, "MBC1"},
    {0x02, "MBC1+RAM"},
    {0x03, "MBC1+RAM+BATTERY"},
    {0x05, "MBC2"},
    {0x06, "MBC2+BATTERY"},
    {0x08, "ROM+RAM"},
    {0x09, "ROM+RAM+BATTERY"},
    {0x0B, "MMM01"},
    {0x0C, "MMM01+RAM"},
    {0x0D, "MMM1+RAM+BATTERY"},
    {0x0F, "MBC3+TIMER+BATTERY"},
    {0x10, "MBC3+TIMER+RAM+BATTERY"},
    {0x11, "MBC3"},
    {0x12, "MBC3+RAM"},
    {0x13, "MBC3+RAM+BATTERY"},
    {0x19, "MBC5"},
    {0x1A, "MBC5+RAM"},
    {0x1B, "MBC5+RAM+BATTERY"},
    {0x1C, "MBC5+RUMBLE"},
    {0x1D, "MBC5+RUMBLE+RAM"},
    {0x1E, "MBC5+RUMBLE+RAM+BATTERY"},
    {0x20, "MBC6"},
    {0x22, "MBC7+SENSOR+RUMBLE+RAM+BATTERY"}
};

std::unordered_map<uint8_t, std::string> rom_size_map = {
    {0x00, "32 KiB - 2 (no banking)"},
    {0x01, "64 KiB - 4"},
    {0x02, "128 KiB - 8"},
    {0x03, "256 KiB - 16"},
    {0x04, "512 KiB - 32"},
    {0x05, "1 MiB - 64"},
    {0x06, "2 MiB - 128"},
    {0x07, "4 MiB - 256"},
    {0x08, "8 MiB - 512"}
};

std::unordered_map<uint8_t, std::string> ram_size_map = {
    {0x00, "0 - No RAM"},
    {0x01, "- - Unused"},
    {0x02, "8 KiB - 1 bank"},
    {0x03, "32 Kib - 4 banks of 8KiB each"},
    {0x04, "128 Kib - 16 banks of 8KiB each"},
    {0x05, "64 Kib - 8 banks of 8KiB each"}
};

bool Cartridge::load_cart(char* path){
    //this->filename = path.substr(path.find_last_of("/"));
    
    FILE* fp = fopen(path, "r");

    if(!fp) {
        printf("Failed to open on path: %s\n", path);
        return false;
    }

    printf("Opened: %s\n", this->filename.c_str());

    fseek(fp, 0, SEEK_END);
    this->rom_size = ftell(fp);
    rewind(fp);

    this->rom_data = (uint8_t* )malloc(this->rom_size);
    if(this->rom_data == nullptr){
        printf("Failed to allocate memory to rom_data\n");
        return false;
    }
    fread(this->rom_data, this->rom_size, 1, fp);
    fclose(fp);
    this->header = (rom_header*)(this->rom_data + 0x100);

    printf("Cartridge Loaded:\n");
    printf("\t Title : %s\n", this->header->title);
    printf("\t New licensee code : %2.2X - %s\n", this->header->old_licensee_code, old_licensee_code_map[this->header->old_licensee_code].c_str());
    printf("\t Cartridge type : %2.2X - %s\n", this->header->catrige_type, cartridge_type_map[this->header->catrige_type].c_str());
    printf("\t ROM size - ROM banks : %2.2X - %s\n", this->header->rom_size, rom_size_map[this->header->rom_size].c_str());
    printf("\t RAM size : %2.2X - %s\n", this->header->ram_size, ram_size_map[this->header->ram_size].c_str());
    printf("\t ROM version : %2.2X\n", this->header->maks_rom_version_number);


    int x = 0;
    for(int i = 0x0134; i <= 0x014C; i++){
        x = x - this->rom_data[i] - 1;
    }

    printf("\t Checksum : %2.2X (%s)\n", this->header->header_checksum, (x & 0xFF) ? "PASSED" : "FAILED");
    return true;
}

uint8_t Cartridge::read_cart(uint16_t addr){
    return this->rom_data[addr];
}

void Cartridge::write_cart(uint16_t addr, uint8_t val){
    
}