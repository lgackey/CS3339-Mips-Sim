#include "RegisterFile.h"

RegisterFile::RegisterFile() {
    regs.fill(0); // initialize all registers to 0
}

int RegisterFile::read(int regNum) const {
    return regs[regNum];
}

void RegisterFile::write(int regNum, int value) {
    if (regNum != 0) regs[regNum] = value; // $0 is always 0
}
