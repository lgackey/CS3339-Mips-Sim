#include "ALU.h"


void ALU::ADD(int reg1, int reg2, int reg3) {
    reg_file->write(reg1, (reg_file->read(reg2) + reg_file->read(reg3)));
}

void ALU::ADDI(int reg1, int reg2, int num) {
    reg_file->write(reg1, (reg_file->read(reg2) + num));
}

void ALU::SUB(int reg1, int reg2, int reg3) {
    reg_file->write(reg1, (reg_file->read(reg2) - reg_file->read(reg3)));
}

void ALU::MUL(int reg1, int reg2, int reg3) {
    reg_file->write(reg1, (reg_file->read(reg2) * reg_file->read(reg3)));
}

void ALU::AND(int reg1, int reg2, int reg3) {
    reg_file->write(reg1, (reg_file->read(reg2) & reg_file->read(reg3)));
}

void ALU::OR(int reg1, int reg2, int reg3) {
    reg_file->write(reg1, (reg_file->read(reg2) | reg_file->read(reg3)));
}

void ALU::SLL(int reg1, int reg2, int samt) {
    reg_file->write(reg1, (reg_file->read(reg2) << samt));
}

void ALU::SRL(int reg1, int reg2, int samt) {
    reg_file->write(reg1, (reg_file->read(reg2) >> samt));
}

