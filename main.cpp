#include <iostream>
#include "CPU/cpu.h"
#include <bitset>
using namespace std;

int main() {

    Registers registers;
    CPU cpu;

    registers.A = 0x19; // 00011001
    reg mem = 0x23; // 00100011

    //00011001 & 00100011 should = 00000001
    cpu.op_and(&registers);

    cout << "Result: " << (bitset<8>)registers.A << endl;
    return 0;
}