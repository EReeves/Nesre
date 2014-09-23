//Holds the registers for the NES CPU, Ricoh 2A03.
//A lot of the information for these was grabbed from an old blog post that I lost.

typedef unsigned char reg; //All but one of the registers are 8bit.
typedef unsigned short reg_pc; //16 bit for the PC register.
typedef unsigned short instruction;
typedef bool bit;

//The P register holds processor flags
struct Flags {
    bit
            C, //Carry flag.
            Z, //Zero flag.
            I, //Interrupt flag.
            D, //Decimal mode flag.
            B, //Software interrupt (BRK instruction) occured.
            V, //Overflow.
            S; //Sign flag, set if result is positive.=
};

enum Address_Mode
{
    IMMEDIATE,
    ABSOLUTE,
    ZP_ABSOLUTE,
    IMPLIED,
    ACCUMULATOR,
    INDEXED,
    ZP_INDEXED,
    INDIRECT,
    PRE_INDIRECT,
    POST_INDIRECT,
    RELATIVE,
    INSTRUCTION, //Special mode that doesn't exist on the CPU, used when reading the first part of an instruction.
    NONE //Likewise, default state.
};

class Registers
{
public:

    Registers();
    //General purpose registers.
    reg A, //The accumulator.
        X, Y; //For holding things such as iteration counts, the X register can also be used to get/set the SP register.

    //Special purpose registers.

    /*SP Points to the current size of the stack and is the least significant byte of an address starting at offset 0x100 in memory.
    * This means that the stack is located in memory from 0x100 to 0x1FF. The SP grows downwards in memory space,
    * meaning that pushing onto the stack will decrement the stack pointer, and popping will increment it. */
    reg SP;

    //P Holds the processor flags, enum for those declared further down.
    Flags P;

    reg_pc PC;
};