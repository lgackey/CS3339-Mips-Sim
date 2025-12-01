#pragma once
#include <bitset>
#include "../register/RegisterFile.h"

class ALU {
private:
    RegisterFile* reg_file;

public:
    ALU(RegisterFile& reg) {
        reg_file = &reg;
    }
    void ADD(int reg1, int reg2, int reg3);
    void ADDI(int reg1, int reg2, int num);
    void SUB(int reg1, int reg2, int reg3);
    void MUL(int reg1, int reg2, int reg3);

    void AND(int reg1, int reg2, int reg3);
    void OR(int reg1, int reg2, int reg3);

    void SLL(int reg1, int reg2, int samt);
    void SRL(int reg1, int reg2, int samt);

};
