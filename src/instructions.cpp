#include "../inc/instructions.h"
#include <cstdint>
#include <cstdio>
#include <stdexcept>
#include <unordered_map>

std::unordered_map<uint8_t, instruction> instruction_map = {
    {0x00, {IT_NOP, AT_NO}}
};

instruction* instruction_by_opcode(uint8_t opcode){

    try{
        return& instruction_map.at(opcode);
    } catch (const std::out_of_range& e){
        printf("Unknown instruction: %02X\n", opcode);
        exit(-4);
    }
}