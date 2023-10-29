#include <stdint.h>

#define MEM_MAX (1 << 16)

//memory storage
uint16_t memory[MEM_MAX]; /*128 KB*/

//16-bit registers
enum{
    R_R0 = 0,
    R_R1,
    R_R2,
    R_R3,
    R_R4,
    R_R5,
    R_R6,
    R_R7,
    R_PC, /*address of next instruction*/
    R_COND, /*info about previous calculation*/
    R_CNT
};

//register storage
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

//main loop

int main(int argc, const char* argv[]){
    //load args
    if(argc < 2){
        printf("lc3 [image-file1] ...\n");
        exit(2);
    }

    for(int j = 1; j < argc; ++j){
        if(!read_img(argv[j])){
            printf("failed to load image: %s\n", argv[j]);
            exit(1);
        }
    }



    //setup


    reg[R_COND] = FL_ZRO;

    //setting pc to default start
    enum {PC_START = 0x3000};
    reg[R_PC] = PC_START;

    int run = 1;
    while(run){
        //fetch
        uint16_t instr = mem_read(reg[R_PC]++);
        uint16_t op = instr >> 12;

        switch(op){
            case OP_ADD:
                //Destination
                uint16_t DR = (instr >> 9) & 0x7;

                //1st operand
                uint16_t OP1 = (instr >> 6) & 0x7;

                uint16_t immed_flag = (instr >> 5) & 0x1;

                if(immed_flag){
                    uint16_t imm5 = sign_extend(instr & 0x1F, 5);
                    reg[DR] = reg[OP1] + imm5;
                }
                else{
                    uint16_t OP2 = (instr) & 0x7;
                    reg[DR] = reg[OP1] + reg[OP2];
                }

                update_flags(DR);

                break;
            case OP_AND:
                //and
                break;
            case OP_NOT:
                //not
                break;
            case OP_BR:
                //br
                break;
            case OP_JMP:
                //jmp
                break;
            case OP_JSR:
                //jsr
                break;
            case OP_LD:
                //ld
                break;
            case OP_LDI:
                //ldi
                break;
            case OP_LDR:
                //ldr
                break;
            case OP_LEA:
                //lea
                break;
            case OP_ST:
                //st
                break;
            case OP_STI:
                //sti
                break;
            case OP_STR:
                //str
                break;
            case OP_TRAP:
                //trap
                break;
            case OP_RES:
            case OP_RTI:
            default:
                //bad
                break;
        }
    }
}

uint16_t sign_extend(uint16_t x, int bit_cnt){
    if ((x >> (bit_cnt - 1)) & 1){
        x |= (0xFFFF << bit_cnt);
    }
    return x;
}

void update_flags(uint16_t i){
    if(reg[i] == 0){
        reg[R_COND] = FL_ZRO;
    }
    else if(reg[i] >> 15){
        reg[R_COND] = FL_NEG;
    }
    else{
        reg[R_COND] = FL_POS;
    }
}







