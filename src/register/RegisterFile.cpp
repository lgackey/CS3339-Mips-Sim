#include "RegisterFile.h"

RegisterFile::RegisterFile() {
    regs.fill(0); // initialize all registers to 0
}

int RegisterFile::read(int regNum) const {
     if (regNum < 0 || regNum >= 32) {
        throw std::out_of_range("Register index out of range (0-31)");
    }
    return regs[regNum];
}

// Write a value to a register (except $0)
void RegisterFile::write(int regNum, int value) {
    if (regNum <= 0 || regNum >= 32) return; // $0 immutable, others protected by bounds
    regs[regNum] = value;
}

// Reset all registers to 0
void RegisterFile::reset() {
    regs.fill(0);
}

// Print all registers (useful for debug mode)
void RegisterFile::print() const {
    std::cout << "Register File State:\n";
    for (int i = 0; i < 32; ++i) {
        std::cout << "R" << i << ": " << regs[i] << "\n";
    }
}
