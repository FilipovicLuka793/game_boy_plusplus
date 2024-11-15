#ifndef _INSTRUCTIONS_H_
#define _INSTRUCTIONS_H_

typedef enum {
    CT_NONE,
    CT_NZ,
    CT_Z,
    CT_NC,
    CT_C
} condition_type;

typedef enum {
    IT_NONE,
    IT_NOP,
    IT_LD,
    IT_INC,
    IT_DEC,
    IT_RLCA,
    IT_ADD,
    IT_RRCA,
    IT_STOP,
    IT_RLA,
    IT_JR,
    IT_RRA,
    IT_DAA,
    IT_CPL,
    IT_SCF,
    IT_CCF,
    IT_HALT,
    IT_ADC,
    IT_SUB,
    IT_SBC,
    IT_AND,
    IT_XOR,
    IT_OR,
    IT_CP,
    IT_RET,
    IT_POP,
    IT_JP,
    IT_CALL,
    IT_PUSH,
    IT_RST,
    IT_PREFIX,
    IT_RETI,
    IT_DI,
    IT_EI,
    //CB:
    IT_RLC,
    IT_RRC,
    IT_RL,
    IT_RR,
    IT_SLA,
    IT_SRA,
    IT_SWAP,
    IT_SRL,
    IT_BIT,
    IT_RES,
    IT_SET
} instruction_type;

typedef enum {
    RT_NONE,
    RT_A,
    RT_F,
    RT_B,
    RT_C,
    RT_D,
    RT_E,
    RT_H,
    RT_L,
    RT_AF,
    RT_BC,
    RT_DE,
    RT_HL,
    RT_PC,
    RT_SP
} register_type;

typedef enum {

} addres_type;

#endif