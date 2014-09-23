//NES CPU emulation, Ricoh 2A03.
#include "registers.h"
#include <vector>

//All the information associated with an instruction.
struct Op
{
    Address_Mode AMD = NONE; //Address mode.
    reg M = 0x00; //Operand value.
    reg_pc MA = 0x0000; //16 bit address for absolute and zero page address mode.
    int cycles; //The cycles in the operation.
    int bytes; //The bytes to read.
    int c_count; //The cycle count.
    instruction inst; //The instruction opcode.
};


class CPU
{
public:

    CPU(std::vector<reg> *mem);

    Registers rg;
    void cycle();

    //Instruction set.

    //ADC, Add memory to accumulator with carry.
    void op_adc();
    //AND, "AND" memory with accumulator.
    void op_and();
    //ASL, Shift left one bit.
    void op_asl();
    //BCC, Branch on carry clear.
    void op_bcc();


    //LDA, Load accumulator with memory.
    void op_lda();

    //Memory
    std::vector<reg> memory;

private:

    bool new_instruction = true;
    int memory_pos = 0;
    //Current operation.
    Op op;

    void (CPU::*op_function)(); //Holds operation function.

    //operation helper functions.
    void oph_sflag(reg m);

    void oph_vflag(reg m);

    void oph_zflag(reg m);

    //
    void sort_opcode(reg oper);
};
