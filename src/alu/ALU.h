#pragma once

#include "../register/RegisterFile.h"

class ALU {
private:
    RegisterFile* reg_file;

public:
    ALU(RegisterFile& reg) {
        reg_file = &reg;
    }
    int ADD(int reg1, int reg2, int reg3);
    int ADDI(int reg1, int reg2, int num);
    int SUB(int reg1, int reg2, int reg3);
    int MUL(int reg1, int reg2, int reg3);

    int AND(int reg1, int reg2, int reg3);
    int OR(int reg1, int reg2, int reg3);

    int SLL(int reg1, int reg2, int samt);
    int SRL(int reg1, int reg2, int samt);

};

