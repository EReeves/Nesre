//NES CPU emulation, Ricoh 2A03.
#include "registers.h"
class CPU
{

public:

    CPU();
    Registers registers;
    void cycle();
    //16bit instructions, blank bytes are filled with 0 so you don't see it in the asm.
    //ASM e.g. stx $FF becomes stx $00FF whereas stx $FF00 stays as $FF00.
    typedef unsigned short instruction;
    instruction inst = 0x0000;

    //Instruction set.

    //ADC, Add memory to accumulator with carry.
    void op_adc(Registers* regs);
    //AND, "AND" memory with accumulator.
    void op_and(Registers* regs);
    //ASL, Shift left one bit.
    void op_asl(Registers* regs);
    //BCC, Branch on carry clear.
    void op_bcc(Registers* regs);

private:

    //operation helper functions.

    void oph_sflag(Registers* regs, reg m);
    void oph_vflag(Registers* regs, reg m);
    void oph_zflag(Registers *regs, reg m);

};
