#include <iostream>
#include <iomanip>
#include <vector>
#include "CPU/cpu.h"
using namespace std;

int main() {

    vector<reg> memory(2);
    memory[0] = 0xA9;
    memory[1] = 0xFF;
    //LDA 0xFF

    CPU cpu = CPU(&memory);

    cpu.cycle();

    cout << "Result: " << setbase(16) << "0x" << (int) cpu.rg.A << endl;
    return 0;
}