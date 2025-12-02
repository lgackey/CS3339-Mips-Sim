#include "ALU.h"

//Adds reg2 and reg3 and stores the value at reg1: reg1 = reg2 + reg3
int ALU::ADD(int reg1, int reg2, int reg3) {
    return reg_file->write(reg1, (reg_file->read(reg2) + reg_file->read(reg3)));
}

//Adds reg2 and num and stores the value at reg1: reg1 = reg2 + num
int ALU::ADDI(int reg1, int reg2, int num) {
    return reg_file->write(reg1, (reg_file->read(reg2) + num));
}

//Subtracts reg2 from reg2 and stores the value at reg1: reg1 = reg2 - reg3
int ALU::SUB(int reg1, int reg2, int reg3) {
    return reg_file->write(reg1, (reg_file->read(reg2) - reg_file->read(reg3)));
}

//Multiplies reg2 and reg 3 and stores the value at reg1: reg1 = reg2 * reg3
int ALU::MUL(int reg1, int reg2, int reg3) {
    return reg_file->write(reg1, (reg_file->read(reg2) * reg_file->read(reg3)));
}

//Bitwise AND between reg2 and reg 3 that is stored in reg1
int ALU::AND(int reg1, int reg2, int reg3) {
    return reg_file->write(reg1, (reg_file->read(reg2) & reg_file->read(reg3)));
}

//Bitwise OR between reg2 and reg3 that is stored in reg1
int ALU::OR(int reg1, int reg2, int reg3) {
    return reg_file->write(reg1, (reg_file->read(reg2) | reg_file->read(reg3)));
}

//Shift reg2 left by samt and store the value in reg1
int ALU::SLL(int reg1, int reg2, int samt) {
    return reg_file->write(reg1, (reg_file->read(reg2) << samt));
}

//Shift reg2 right by samt and store the value in reg1
int ALU::SRL(int reg1, int reg2, int samt) {
    return reg_file->write(reg1, (reg_file->read(reg2) >> samt));
}

