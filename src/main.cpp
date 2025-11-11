#include <iostream>
#include "alu/ALU.h"
#include "register/RegisterFile.h"

int main() {
    // --- ALU test ---
    ALU alu;
    int a = 10, b = 5;

    std::cout << "ALU Tests:\n";
    std::cout << "ADD: " << alu.add(a,b) << "\n";
    std::cout << "SUB: " << alu.sub(a,b) << "\n";
    std::cout << "MUL: " << alu.mul(a,b) << "\n";
    std::cout << "AND: " << alu.bitwise_and(a,b) << "\n";
    std::cout << "OR: " << alu.bitwise_or(a,b) << "\n";
    std::cout << "SLL: " << alu.sll(a,2) << "\n";
    std::cout << "SRL: " << alu.srl(a,1) << "\n";

    // --- Register File test ---
    RegisterFile rf;
    rf.write(1, 42); // write value to register 1
    rf.write(2, 100); // write value to register 2

    std::cout << "\nRegister File Tests:\n";
    std::cout << "Register 1: " << rf.read(1) << "\n"; // should print 42
    std::cout << "Register 2: " << rf.read(2) << "\n"; // should print 100
    std::cout << "Register 0: " << rf.read(0) << "\n"; // should print 0 (always zero)

    return 0;
}
