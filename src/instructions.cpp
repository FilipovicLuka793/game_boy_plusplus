#include "../inc/instructions.h"
#include <cstdint>
#include <cstdio>
#include <stdexcept>
#include <string>
#include <unordered_map>

std::unordered_map<uint8_t, instruction> instruction_map = {
    {0x00, {IT_NOP, AT_NO}},
    {0x10, {IT_STOP}},
    {0x07, {IT_RLCA}},
    {0x17, {IT_RLA}},
    {0x37, {IT_SCF}},
    {0x2F, {IT_CPL}},
    {0x3F, {IT_CCF}},
    {0x0F, {IT_RRCA}},
    {0x1F, {IT_RRA}},
    {0x76, {IT_HALT}},
    {0xCB, {IT_PREFIX, AT_D8}},
    {0x27, {IT_DAA}},

    // JP
    {0xC3, {IT_JP, AT_IMM16}},
    {0xC2, {IT_JP, AT_IMM16, RT_NONE, RT_NONE, CT_NZ}},
    {0xD2, {IT_JP, AT_IMM16, RT_NONE, RT_NONE, CT_NC}},
    {0xCA, {IT_JP, AT_IMM16, RT_NONE, RT_NONE, CT_Z}},
    {0xD2, {IT_JP, AT_IMM16, RT_NONE, RT_NONE, CT_C}},
    {0xE9, {IT_JP, AT_R, RT_HL}},

    // DI-EI
    {0xF3, {IT_DI, AT_NO}},
    {0xFB, {IT_EI, AT_NO}},

    // AND
    {0xA0, {IT_AND, AT_R, RT_B}},
    {0xA1, {IT_AND, AT_R, RT_C}},
    {0xA2, {IT_AND, AT_R, RT_D}},
    {0xA3, {IT_AND, AT_R, RT_E}},
    {0xA4, {IT_AND, AT_R, RT_H}},
    {0xA5, {IT_AND, AT_R, RT_L}},
    {0xA6, {IT_AND, AT_R_MR, RT_A, RT_HL}},
    {0xA7, {IT_AND, AT_R, RT_A}},

    {0xE6, {IT_AND, AT_R_D8, RT_A}},

    // XOR
    {0xA8, {IT_XOR, AT_R, RT_B}},
    {0xA9, {IT_XOR, AT_R, RT_C}},
    {0xAA, {IT_XOR, AT_R, RT_D}},
    {0xAB, {IT_XOR, AT_R, RT_E}},
    {0xAC, {IT_XOR, AT_R, RT_H}},
    {0xAD, {IT_XOR, AT_R, RT_L}},
    {0xAE, {IT_XOR, AT_R_MR, RT_A, RT_HL}},
    {0xAF, {IT_XOR, AT_R, RT_A}},

    {0xEE, {IT_XOR, AT_R_D8, RT_A}},

    // OR
    {0xB0, {IT_OR, AT_R, RT_B}},
    {0xB1, {IT_OR, AT_R, RT_C}},
    {0xB2, {IT_OR, AT_R, RT_D}},
    {0xB3, {IT_OR, AT_R, RT_E}},
    {0xB4, {IT_OR, AT_R, RT_H}},
    {0xB5, {IT_OR, AT_R, RT_L}},
    {0xB6, {IT_OR, AT_R_MR, RT_A, RT_HL}},
    {0xB7, {IT_OR, AT_R, RT_A}},

    {0xF6, {IT_OR, AT_R_D8, RT_A}},

    // CP
    {0xB8, {IT_CP, AT_R, RT_B}},
    {0xB9, {IT_CP, AT_R, RT_C}},
    {0xBA, {IT_CP, AT_R, RT_D}},
    {0xBB, {IT_CP, AT_R, RT_E}},
    {0xBC, {IT_CP, AT_R, RT_H}},
    {0xBD, {IT_CP, AT_R, RT_L}},
    {0xBE, {IT_CP, AT_R_MR, RT_A, RT_HL}},
    {0xBF, {IT_CP, AT_R, RT_A}},
    {0xFE, {IT_CP, AT_R_D8, RT_A}},

    // LD
    {0x01, {IT_LD, AT_R_D16, RT_BC}},
    {0x11, {IT_LD, AT_R_D16, RT_DE}},
    {0x21, {IT_LD, AT_R_D16, RT_HL}},
    {0x31, {IT_LD, AT_R_D16, RT_SP}},
    {0x0E, {IT_LD, AT_R_D8, RT_C}},
    {0x06, {IT_LD, AT_R_D8, RT_B}},
    {0x16, {IT_LD, AT_R_D8, RT_D}},
    {0x1E, {IT_LD, AT_R_D8, RT_E}},
    {0x26, {IT_LD, AT_R_D8, RT_H}},
    {0x2E, {IT_LD, AT_R_D8, RT_L}},
    {0x3E, {IT_LD, AT_R_D8, RT_A}},
    {0x40, {IT_LD, AT_R_R, RT_B, RT_B}},
    {0x41, {IT_LD, AT_R_R, RT_B, RT_C}},
    {0x42, {IT_LD, AT_R_R, RT_B, RT_D}},
    {0x43, {IT_LD, AT_R_R, RT_B, RT_E}},
    {0x44, {IT_LD, AT_R_R, RT_B, RT_H}},
    {0x45, {IT_LD, AT_R_R, RT_B, RT_L}},
    {0x46, {IT_LD, AT_R_MR, RT_B, RT_HL}},
    {0x47, {IT_LD, AT_R_R, RT_B, RT_A}},
    {0x48, {IT_LD, AT_R_R, RT_C, RT_B}},
    {0x49, {IT_LD, AT_R_R, RT_C, RT_C}},
    {0x4A, {IT_LD, AT_R_R, RT_C, RT_D}},
    {0x4B, {IT_LD, AT_R_R, RT_C, RT_E}},
    {0x4C, {IT_LD, AT_R_R, RT_C, RT_H}},
    {0x4D, {IT_LD, AT_R_R, RT_C, RT_L}},
    {0x4E, {IT_LD, AT_R_MR, RT_C, RT_HL}},
    {0x4F, {IT_LD, AT_R_R, RT_C, RT_A}},
    {0x50, {IT_LD, AT_R_R, RT_D, RT_B}},
    {0x51, {IT_LD, AT_R_R, RT_D, RT_C}},
    {0x52, {IT_LD, AT_R_R, RT_D, RT_D}},
    {0x53, {IT_LD, AT_R_R, RT_D, RT_E}},
    {0x54, {IT_LD, AT_R_R, RT_D, RT_H}},
    {0x55, {IT_LD, AT_R_R, RT_D, RT_L}},
    {0x56, {IT_LD, AT_R_MR, RT_D, RT_HL}},
    {0x57, {IT_LD, AT_R_R, RT_D, RT_A}},
    {0x58, {IT_LD, AT_R_R, RT_E, RT_B}},
    {0x59, {IT_LD, AT_R_R, RT_E, RT_C}},
    {0x5A, {IT_LD, AT_R_R, RT_E, RT_D}},
    {0x5B, {IT_LD, AT_R_R, RT_E, RT_E}},
    {0x5C, {IT_LD, AT_R_R, RT_E, RT_H}},
    {0x5D, {IT_LD, AT_R_R, RT_E, RT_L}},
    {0x5E, {IT_LD, AT_R_MR, RT_E, RT_HL}},
    {0x5F, {IT_LD, AT_R_R, RT_E, RT_A}},
    {0x60, {IT_LD, AT_R_R, RT_H, RT_B}},
    {0x61, {IT_LD, AT_R_R, RT_H, RT_C}},
    {0x62, {IT_LD, AT_R_R, RT_H, RT_D}},
    {0x63, {IT_LD, AT_R_R, RT_H, RT_E}},
    {0x64, {IT_LD, AT_R_R, RT_H, RT_H}},
    {0x65, {IT_LD, AT_R_R, RT_H, RT_L}},
    {0x66, {IT_LD, AT_R_MR, RT_H, RT_HL}},
    {0x67, {IT_LD, AT_R_R, RT_H, RT_A}},
    {0x68, {IT_LD, AT_R_R, RT_L, RT_B}},
    {0x69, {IT_LD, AT_R_R, RT_L, RT_C}},
    {0x6A, {IT_LD, AT_R_R, RT_L, RT_D}},
    {0x6B, {IT_LD, AT_R_R, RT_L, RT_E}},
    {0x6C, {IT_LD, AT_R_R, RT_L, RT_H}},
    {0x6D, {IT_LD, AT_R_R, RT_L, RT_L}},
    {0x6E, {IT_LD, AT_R_MR, RT_L, RT_HL}},
    {0x6F, {IT_LD, AT_R_R, RT_L, RT_A}},
    {0x70, {IT_LD, AT_MR_R, RT_HL, RT_B}},
    {0x71, {IT_LD, AT_MR_R, RT_HL, RT_C}},
    {0x72, {IT_LD, AT_MR_R, RT_HL, RT_D}},
    {0x73, {IT_LD, AT_MR_R, RT_HL, RT_E}},
    {0x74, {IT_LD, AT_MR_R, RT_HL, RT_H}},
    {0x75, {IT_LD, AT_MR_R, RT_HL, RT_L}},
    {0x77, {IT_LD, AT_MR_R, RT_HL, RT_A}},
    {0x78, {IT_LD, AT_R_R, RT_A, RT_B}},
    {0x79, {IT_LD, AT_R_R, RT_A, RT_C}},
    {0x7A, {IT_LD, AT_R_R, RT_A, RT_D}},
    {0x7B, {IT_LD, AT_R_R, RT_A, RT_E}},
    {0x7C, {IT_LD, AT_R_R, RT_A, RT_H}},
    {0x7D, {IT_LD, AT_R_R, RT_A, RT_L}},
    {0x7E, {IT_LD, AT_R_MR, RT_A, RT_HL}},
    {0x7F, {IT_LD, AT_R_R, RT_A, RT_A}},
    {0x02, {IT_LD, AT_MR_R, RT_BC, RT_A}},
    {0x12, {IT_LD, AT_MR_R, RT_DE, RT_A}},
    {0x22, {IT_LD, AT_HLI_R, RT_HL, RT_A}},
    {0x32, {IT_LD, AT_HLD_R, RT_HL, RT_A}},
    {0x0A, {IT_LD, AT_R_MR, RT_A, RT_BC}},
    {0x1A, {IT_LD, AT_R_MR, RT_A, RT_DE}},
    {0x2A, {IT_LD, AT_R_HLI, RT_A, RT_HL}},
    {0x3A, {IT_LD, AT_R_HLD, RT_A, RT_HL}},
    {0x36, {IT_LD, AT_MR_D8, RT_HL}},
    {0xE2, {IT_LD, AT_MR_R, RT_C, RT_A}},
    {0xF2, {IT_LD, AT_R_MR, RT_A, RT_C}},
    {0xEA, {IT_LD, AT_A16_R, RT_NONE, RT_A}},
    {0xFA, {IT_LD, AT_R_A16, RT_A}},
    {0x08, {IT_LD, AT_A16_R, RT_NONE, RT_SP}},
    {0xF9, {IT_LD, AT_R_R, RT_SP, RT_HL}},
    {0xF8, {IT_LD, AT_HL_SPR, RT_HL, RT_SP}},
    {0xF9, {IT_LD, AT_R_R, RT_SP, RT_HL}},

    // LDH
    {0xE0, {IT_LDH, AT_A8_R, RT_NONE, RT_A}},
    {0xF0, {IT_LDH, AT_R_A8, RT_A}},

    // INC
    {0x04, {IT_INC, AT_R, RT_B}},
    {0x14, {IT_INC, AT_R, RT_D}},
    {0x24, {IT_INC, AT_R, RT_H}},
    {0x0C, {IT_INC, AT_R, RT_C}},
    {0x1C, {IT_INC, AT_R, RT_E}},
    {0x2C, {IT_INC, AT_R, RT_L}},
    {0x3C, {IT_INC, AT_R, RT_A}},
    {0x03, {IT_INC, AT_R, RT_BC}},
    {0x13, {IT_INC, AT_R, RT_DE}},
    {0x23, {IT_INC, AT_R, RT_HL}},
    {0x33, {IT_INC, AT_R, RT_SP}},
    {0x34, {IT_INC, AT_MR, RT_HL}},

    // DEC
    {0x05, {IT_DEC, AT_R, RT_B}},
    {0x15, {IT_DEC, AT_R, RT_D}},
    {0x25, {IT_DEC, AT_R, RT_H}},
    {0x0D, {IT_DEC, AT_R, RT_C}},
    {0x1D, {IT_DEC, AT_R, RT_E}},
    {0x2D, {IT_DEC, AT_R, RT_L}},
    {0x3D, {IT_DEC, AT_R, RT_A}},
    {0x0B, {IT_DEC, AT_R, RT_BC}},
    {0x1B, {IT_DEC, AT_R, RT_DE}},
    {0x2B, {IT_DEC, AT_R, RT_HL}},
    {0x3B, {IT_DEC, AT_R, RT_SP}},
    {0x35, {IT_DEC, AT_MR, RT_HL}},

    // JR
    {0x20, {IT_JR, AT_D8, RT_NONE, RT_NONE, CT_NZ}},
    {0x30, {IT_JR, AT_D8, RT_NONE, RT_NONE, CT_NC}},
    {0x18, {IT_JR, AT_D8, RT_NONE, RT_NONE, CT_NONE}},
    {0x28, {IT_JR, AT_D8, RT_NONE, RT_NONE, CT_Z}},
    {0x38, {IT_JR, AT_D8, RT_NONE, RT_NONE, CT_C}},

    // PUSH/POP
    {0xC1, {IT_POP, AT_R, RT_BC}},
    {0xD1, {IT_POP, AT_R, RT_DE}},
    {0xE1, {IT_POP, AT_R, RT_HL}},
    {0xF1, {IT_POP, AT_R, RT_AF}},

    {0xC5, {IT_PUSH, AT_R, RT_BC}},
    {0xD5, {IT_PUSH, AT_R, RT_DE}},
    {0xE5, {IT_PUSH, AT_R, RT_HL}},
    {0xF5, {IT_PUSH, AT_R, RT_AF}},

    // Calls
    {0xCD, {IT_CALL, AT_IMM16}},
    {0xCC, {IT_CALL, AT_IMM16, RT_NONE, RT_NONE, CT_Z}},
    {0xDC, {IT_CALL, AT_IMM16, RT_NONE, RT_NONE, CT_C}},
    {0xC4, {IT_CALL, AT_IMM16, RT_NONE, RT_NONE, CT_NZ}},
    {0xD4, {IT_CALL, AT_IMM16, RT_NONE, RT_NONE, CT_NC}},

    // RET
    {0xC0, {IT_RET, AT_NO, RT_NONE, RT_NONE, CT_NZ}},
    {0xD0, {IT_RET, AT_NO, RT_NONE, RT_NONE, CT_NC}},
    {0xC8, {IT_RET, AT_NO, RT_NONE, RT_NONE, CT_Z}},
    {0xD8, {IT_RET, AT_NO, RT_NONE, RT_NONE, CT_C}},
    {0xC9, {IT_RET, AT_NO, RT_NONE, RT_NONE, CT_NONE}},
    {0xD9, {IT_RETI, AT_NO, RT_NONE, RT_NONE, CT_NONE}},

    // RST
    {0xC7, {IT_RST, AT_NO, RT_NONE, RT_NONE, CT_NONE, 0x00}},
    {0xCF, {IT_RST, AT_NO, RT_NONE, RT_NONE, CT_NONE, 0x08}},
    {0xD7, {IT_RST, AT_NO, RT_NONE, RT_NONE, CT_NONE, 0x10}},
    {0xDF, {IT_RST, AT_NO, RT_NONE, RT_NONE, CT_NONE, 0x18}},
    {0xE7, {IT_RST, AT_NO, RT_NONE, RT_NONE, CT_NONE, 0x20}},
    {0xEF, {IT_RST, AT_NO, RT_NONE, RT_NONE, CT_NONE, 0x28}},
    {0xF7, {IT_RST, AT_NO, RT_NONE, RT_NONE, CT_NONE, 0x30}},
    {0xFF, {IT_RST, AT_NO, RT_NONE, RT_NONE, CT_NONE, 0x38}},

    // ADD
    {0x09, {IT_ADD, AT_R_R, RT_HL, RT_BC}},
    {0x19, {IT_ADD, AT_R_R, RT_HL, RT_DE}},
    {0x29, {IT_ADD, AT_R_R, RT_HL, RT_HL}},
    {0x39, {IT_ADD, AT_R_R, RT_HL, RT_SP}},

    {0x80, {IT_ADD, AT_R_R, RT_A, RT_B}},
    {0x81, {IT_ADD, AT_R_R, RT_A, RT_C}},
    {0x82, {IT_ADD, AT_R_R, RT_A, RT_D}},
    {0x83, {IT_ADD, AT_R_R, RT_A, RT_E}},
    {0x84, {IT_ADD, AT_R_R, RT_A, RT_H}},
    {0x85, {IT_ADD, AT_R_R, RT_A, RT_L}},
    {0x86, {IT_ADD, AT_R_MR, RT_A, RT_HL}},
    {0x87, {IT_ADD, AT_R_R, RT_A, RT_A}},

    {0xC6,
     {
         IT_ADD,
         AT_R_D8,
         RT_A,
     }},
    {0xE8, {IT_ADD, AT_R_D8, RT_SP}},

    // ADC
    {0x88, {IT_ADC, AT_R_R, RT_A, RT_B}},
    {0x89, {IT_ADC, AT_R_R, RT_A, RT_C}},
    {0x8A, {IT_ADC, AT_R_R, RT_A, RT_D}},
    {0x8B, {IT_ADC, AT_R_R, RT_A, RT_E}},
    {0x8C, {IT_ADC, AT_R_R, RT_A, RT_H}},
    {0x8D, {IT_ADC, AT_R_R, RT_A, RT_L}},
    {0x8E, {IT_ADC, AT_R_MR, RT_A, RT_HL}},
    {0x8F, {IT_ADC, AT_R_R, RT_A, RT_A}},

    {0xCE, {IT_ADC, AT_R_D8, RT_A}},

    // SUB
    {0x90, {IT_SUB, AT_R_R, RT_A, RT_B}},
    {0x91, {IT_SUB, AT_R_R, RT_A, RT_C}},
    {0x92, {IT_SUB, AT_R_R, RT_A, RT_D}},
    {0x93, {IT_SUB, AT_R_R, RT_A, RT_E}},
    {0x94, {IT_SUB, AT_R_R, RT_A, RT_H}},
    {0x95, {IT_SUB, AT_R_R, RT_A, RT_L}},
    {0x96, {IT_SUB, AT_R_MR, RT_A, RT_HL}},
    {0x97, {IT_SUB, AT_R_R, RT_A, RT_A}},

    {0xD6, {IT_SUB, AT_R_D8, RT_A}},

    // SBC
    {0x98, {IT_SBC, AT_R_R, RT_A, RT_B}},
    {0x99, {IT_SBC, AT_R_R, RT_A, RT_C}},
    {0x9A, {IT_SBC, AT_R_R, RT_A, RT_D}},
    {0x9B, {IT_SBC, AT_R_R, RT_A, RT_E}},
    {0x9C, {IT_SBC, AT_R_R, RT_A, RT_H}},
    {0x9D, {IT_SBC, AT_R_R, RT_A, RT_L}},
    {0x9E, {IT_SBC, AT_R_MR, RT_A, RT_HL}},
    {0x9F, {IT_SBC, AT_R_R, RT_A, RT_A}},

    {0xDE, {IT_SBC, AT_R_D8, RT_A}},
};

instruction *instruction_by_opcode(uint8_t opcode) {
  try {
    return &instruction_map.at(opcode);
  } catch (const std::out_of_range &e) {
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
    {IT_LDH, "LDH"},
    // CB:
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
    {IT_SET, "SET"}};

std::string instruction_name(instruction_type it) {
  return ins_name_map.at(it);
}

std::unordered_map<register_type, std::string> reg_name_map = {
    {RT_A, "A"},   {RT_F, "F"},   {RT_B, "B"},   {RT_C, "C"},   {RT_D, "D"},
    {RT_E, "E"},   {RT_H, "H"},   {RT_L, "L"},   {RT_AF, "AF"}, {RT_BC, "BC"},
    {RT_DE, "DE"}, {RT_HL, "HL"}, {RT_PC, "PC"}, {RT_SP, "SP"}};

std::string register_name(register_type rt) {
  try {
    return reg_name_map.at(rt);
  } catch (const std::out_of_range &e) {
    return "--";
  }
}

std::unordered_map<addres_type, std::string> addr_name_map = {
    {AT_IMM16, "AT_IMM16"}, {AT_NO, "AT_NO"},         {AT_R, "AT_R"},
    {AT_R_R, "AT_R_R"},     {AT_R_D16, "AT_R_D16"},   {AT_R_D8, "AT_R_D8"},
    {AT_HLD_R, "AT_HLD_R"}, {AT_HLI_R, "AT_HLI_R"},   {AT_MR_R, "AT_MR_R"},
    {AT_R_MR, "AT_R_MR"},   {AT_R_HLI, "AT_R_HLI"},   {AT_R_HLD, "AT_R_HLD"},
    {AT_MR_D8, "AT_MR_D8"}, {AT_R_A16, "AT_R_A16"},   {AT_A16_R, "AT_A16_R"},
    {AT_D16_R, "AT_D16_R"}, {AT_HL_SPR, "AT_HL_SPR"}, {AT_D8, "AT_D8"},
    {AT_A8_R, "AT_A8_R"},   {AT_R_A8, "AT_R_A8"},     {AT_MR, "AT_MR"},

};

std::string addresing_name(addres_type at) { return addr_name_map.at(at); }
