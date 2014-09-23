#include <stdint.h>
#include <imagehlp.h>
#include "cpu.h"

CPU::CPU() {
};


void CPU::cycle()
{
    switch(registers.AMD)
    {
        case INSTRUCTION:
            //TODO: Sort op code of inst and execute it next cycle.
            break;
        case IMMEDIATE:
            registers.M = inst;
            break;
    }
}

//Instruction set.
/*
    Some common stuff.
    m & 0x80 - Used for carrying because of twos compliment.
    N == S flag, because of weird documentation.
 */

//Helper functions

void CPU::oph_sflag(Registers* regs, reg m)
{
    regs->P.S = m > 0x80;
};

void CPU::oph_vflag(Registers *regs, reg m)
{
    regs->P.V = m > 255 || m < 0;
};

void CPU::oph_zflag(Registers *regs, reg m)
{
    regs->P.Z = m == 0;
};

//

//ADC, Add memory to accumulator with carry. m is the memory being read in. A + M + C -> A, C
void CPU::op_adc(Registers* regs) //Flags N,Z,C,V
{
    uint16_t result = regs-> A + regs->M + regs->P.C;
    //Set flags.
    oph_zflag(regs,result);
    regs->P.C = result > 0xff;
    oph_sflag(regs, result);
    oph_vflag(regs, regs->M);

    //Set result.
    regs->A = (reg)result;
};

//AND, "AND" memory with accumulator. A /\ M -> A
void CPU::op_and(Registers* regs) //Flags N, Z
{
    regs->A &= regs->M;
    oph_sflag(regs, regs->A);
    oph_zflag(regs,regs->A);
};

//ASL, Shift left one bit. C <- |7|6|5|4|3|2|1|0| <- 0
void CPU::op_asl(Registers* regs) //Flags N,Z,C
{
    regs->P.C = regs->M & 0x80;
    regs->M <<= 1;
    oph_sflag(regs, regs->M);
    oph_zflag(regs, regs->M);
    //TODO: Depending on addressing mode, store in memory or accumulator.
};

//BCC, Branch on carry clear.
void op_bcc(Registers* regs)
{
    if(!regs->P.C)
    {

    }
};