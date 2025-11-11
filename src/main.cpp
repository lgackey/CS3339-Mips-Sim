#include <iostream>
#include "alu/ALU.h"
#include "register/RegisterFile.h"
#include "memory/Memory.h"
#include "pipeline/Pipeline.h"
#include "control/ControlUnit.h"

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
    rf.write(1, 42);
    rf.write(2, 100);

    std::cout << "\nRegister File Tests:\n";
    std::cout << "Register 1: " << rf.read(1) << "\n";
    std::cout << "Register 2: " << rf.read(2) << "\n";
    std::cout << "Register 0: " << rf.read(0) << "\n";

    // --- Memory test ---
    Memory mem(256); // 256 words of memory
    mem.storeWord(0, 123);
    mem.storeWord(1, 456);

    std::cout << "\nMemory Tests:\n";
    std::cout << "Memory[0]: " << mem.loadWord(0) << "\n"; // should print 123
    std::cout << "Memory[1]: " << mem.loadWord(1) << "\n"; // should print 456



// After ALU, RegisterFile, Memory initialization
Pipeline pipeline(rf, alu, mem);

pipeline.fetch("ADD $3, $1, $2", 0);
pipeline.decode();
pipeline.execute();
pipeline.memoryAccess();
pipeline.writeBack();

ControlUnit cu;
auto signals = cu.generateSignals("ADD");
std::cout << "ADD signals: RegWrite=" << signals.RegWrite
          << ", ALUOp=" << signals.ALUOp << "\n";

signals = cu.generateSignals("LW");
std::cout << "LW signals: RegWrite=" << signals.RegWrite
          << ", MemRead=" << signals.MemRead
          << ", ALUOp=" << signals.ALUOp << "\n";

}
