#include "../inc/instructions.h"
#include <cstdint>
#include <cstdio>
#include <stdexcept>
#include <string>
#include <unordered_map>

std::unordered_map<uint8_t, instruction> instruction_map = {
    {0x00, {IT_NOP, AT_NO}},
    {0xC3, {IT_JP, AT_IMM16}},
    {0x35, {IT_DEC, AT_MEMR, RT_HL}},

};

instruction* instruction_by_opcode(uint8_t opcode){
    try{
        return& instruction_map.at(opcode);
    } catch (const std::out_of_range& e){
        printf("Unknown instruction: %02X\n", opcode);
        exit(-4);
    }
}

std::unordered_map<instruction_type, std::string> ins_name_map = {
    {IT_NOP, "NOP"},
    {IT_LD, "LD"},
    {IT_INC, "INC"},
    {IT_DEC, "DEC"},
    {IT_RLCA, "RLCA"},
    {IT_ADD, "ADD"},
    {IT_RRCA, "RRCA"},
    {IT_STOP, "STOP"},
    {IT_RLA, "RLA"},
    {IT_JR, "JR"},
    {IT_RRA, "RRA"},
    {IT_DAA, "DAA"},
    {IT_CPL, "CPL"},
    {IT_SCF, "SCF"},
    {IT_CCF, "CCF"},
    {IT_HALT, "HALT"},
    {IT_ADC, "ADC"},
    {IT_SUB, "SUB"},
    {IT_SBC, "SBC"},
    {IT_AND, "AND"},
    {IT_XOR, "XOR"},
    {IT_OR, "OR"},
    {IT_CP, "CP"},
    {IT_RET, "RET"},
    {IT_POP, "POP"},
    {IT_JP, "JP"},
    {IT_CALL, "CALL"},
    {IT_PUSH, "PUSH"},
    {IT_RST, "RST"},
    {IT_PREFIX, "PREFIX"},
    {IT_RETI, "RETI"},
    {IT_DI, "DI"},
    {IT_EI, "EI"},
    //CB:
    {IT_RLC, "RLC"},
    {IT_RRC, "RRC"},
    {IT_RL, "RL"},
    {IT_RR, "RR"},
    {IT_SLA, "SLA"},
    {IT_SRA, "SRA"},
    {IT_SWAP, "SWAP"},
    {IT_SRL, "SRL"},
    {IT_BIT, "BIT"},
    {IT_RES, "RES"},
    {IT_SET, "SET"}
};

std::string instruction_name(instruction_type it){
    return ins_name_map.at(it);
}