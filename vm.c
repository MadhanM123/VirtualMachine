#include <stdint.h>

#define MEM_MAX (1 << 16)

//Memory Storage
uint16_t memory[MEM_MAX]; /*128 KB*/

//16-bit Registers
enum{
    R_R0 = 0,
    R_R1,
    R_R2,
    R_R3,
    R_R4,
    R_R5,
    R_R6,
    R_R7,
    R_PC, /*Address of next instruction*/
    R_COND, /*Info about previous calculation*/
    R_CNT
};

//Register storage
uint16_t reg[R_CNT];

//condition flags
enum{
    FL_POS = 1 << 0, /*P*/
    FL_ZRO = 1 << 1, /*Z*/
    FL_NEG = 1 << 2, /*N*/
};

//opcodes
enum{
    OP_BR = 0, /*branch*/
    OP_ADD, /*add*/
    OP_LD, /*load*/
    OP_ST, /*store*/
    OP_JSR, /*jump register*/
    OP_AND, /*bit and*/
    OP_LDR, /*load register*/
    OP_STR, /* stroe register*/
    OP_RTI, /*unused*/
    OP_NOT, /*bit not*/
    OP_LDI, /*indirect load*/
    OP_STI, /*indirect store*/
    OP_JMP, /*jump*/
    OP_RES, /*reserved*/
    OP_LEA, /*load effective address*/
    OP_TRAP, /*trap*/
};





