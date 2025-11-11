#include <iostream>
#include "alu/ALU.h"

int main() {
    ALU alu;
    int a = 10, b = 5;

    std::cout << "ADD: " << alu.add(a,b) << "\n";
    std::cout << "SUB: " << alu.sub(a,b) << "\n";
    std::cout << "MUL: " << alu.mul(a,b) << "\n";
    std::cout << "AND: " << alu.bitwise_and(a,b) << "\n";
    std::cout << "OR: " << alu.bitwise_or(a,b) << "\n";
    std::cout << "SLL: " << alu.sll(a,2) << "\n";
    std::cout << "SRL: " << alu.srl(a,1) << "\n";

    return 0;
}
