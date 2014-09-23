#include <stdint.h>
#include "cpu.h"

CPU::CPU(std::vector<reg> *mem)
{
    memory = *mem;
};


void CPU::cycle()
{
    while (true)
    {
        if (new_instruction)
        {
            //Return if out of memory.
            if (memory_pos > memory.size() - 1) return;

            //Read instruction from memory.
            sort_opcode(memory[memory_pos]);
            memory_pos++;
            new_instruction = false;
        }

        //Reading data for the instruction in the last cycle.
        if (op.c_count > 0 && op.c_count < op.bytes)
        {
            //Read data.
            switch (op.AMD)
            {
                case IMMEDIATE:
                    op.M = memory[memory_pos];
                    memory_pos++;
                    break;

                case ACCUMULATOR:
                    op.M = rg.A;
            }
        }

        op.c_count++;
        if (op.c_count == op.cycles)
        {
            //End of operation cycle, execute and get ready for a new instruction.
            (this->*op_function)();
            new_instruction = true;
        }
    }
}

//Sets data for operation.
void CPU::sort_opcode(reg oper)
{
    switch (oper)
    {
        case 0xA9: //LDA
            op.cycles = 2;
            op.bytes = 2;
            op.AMD = IMMEDIATE;
            op_function = &CPU::op_lda;
            break;
    }
    op.inst = oper;
    op.c_count = 0;
};

//Instruction set.
/*
    Some common stuff.
    m & 0x80 - Used for carrying because of twos compliment.
    N == S flag, because of weird documentation.
 */

//Helper functions

void CPU::oph_sflag(reg m)
{
    rg.P.S = m > 0x80;
};

void CPU::oph_vflag(reg m)
{
    rg.P.V = m > 255 || m < 0;
};

void CPU::oph_zflag(reg m)
{
    rg.P.Z = m == 0;
};

//Instructions.

//ADC, Add memory to accumulator with carry. m is the memory being read in. A + M + C -> A, C
void CPU::op_adc() //Flags N,Z,C,V
{
    uint16_t result = rg.A + op.M + rg.P.C;
    //Set flags.
    oph_zflag(result);
    rg.P.C = result > 0xff;
    oph_sflag(result);
    oph_vflag(op.M);

    //Set result.
    rg.A = (reg) result;
};

//AND, "AND" memory with accumulator. A /\ M -> A
void CPU::op_and() //Flags N, Z
{
    rg.A &= op.M;
    oph_sflag(rg.A);
    oph_zflag(rg.A);
};

//ASL, Shift left one bit. C <- |7|6|5|4|3|2|1|0| <- 0
void CPU::op_asl() //Flags N,Z,C
{
    rg.P.C = op.M & 0x80;
    op.M <<= 1;
    oph_sflag(op.M);
    oph_zflag(op.M);
    //TODO: Depending on addressing mode, store in memory or accumulator.
};

//BCC, Branch on carry clear.
void op_bcc(Registers* regs)
{
    if(!regs->P.C)
    {

    }
};

//LDA, Load accumulator with memory.
void CPU::op_lda()
{
    rg.A = op.M;
};