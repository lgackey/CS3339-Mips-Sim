#include "ALU.h"

//Adds reg2 and reg3 and stores the value at reg1: reg1 = reg2 + reg3
void ALU::ADD(int reg1, int reg2, int reg3) {
    reg_file->write(reg1, (reg_file->read(reg2) + reg_file->read(reg3)));
}

//Adds reg2 and num and stores the value at reg1: reg1 = reg2 + num
void ALU::ADDI(int reg1, int reg2, int num) {
    reg_file->write(reg1, (reg_file->read(reg2) + num));
}

//Subtracts reg2 from reg2 and stores the value at reg1: reg1 = reg2 - reg3
void ALU::SUB(int reg1, int reg2, int reg3) {
    reg_file->write(reg1, (reg_file->read(reg2) - reg_file->read(reg3)));
}

//Multiplies reg2 and reg 3 and stores the value at reg1: reg1 = reg2 * reg3
void ALU::MUL(int reg1, int reg2, int reg3) {
    reg_file->write(reg1, (reg_file->read(reg2) * reg_file->read(reg3)));
}

//Bitwise AND between reg2 and reg 3 that is stored in reg1
void ALU::AND(int reg1, int reg2, int reg3) {
    reg_file->write(reg1, (reg_file->read(reg2) & reg_file->read(reg3)));
}

//Bitwise OR between reg2 and reg3 that is stored in reg1
void ALU::OR(int reg1, int reg2, int reg3) {
    reg_file->write(reg1, (reg_file->read(reg2) | reg_file->read(reg3)));
}

//shift reg2 left by samt and store the value in reg1
void ALU::SLL(int reg1, int reg2, int samt) {
    reg_file->write(reg1, (reg_file->read(reg2) << samt));
}

//shift reg2 right by samt and store the value in reg1
void ALU::SRL(int reg1, int reg2, int samt) {
    reg_file->write(reg1, (reg_file->read(reg2) >> samt));
}

