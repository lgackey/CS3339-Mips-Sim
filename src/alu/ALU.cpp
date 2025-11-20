#include "ALU.h"
#include <cstdint>

int ALU::add(int regArr[], int reg1, int reg2, int reg3) {
    regArr[reg1] = regArr[reg2] + regArr[reg3];
    return regArr[reg1];
}

int ALU::addi(int regArr[], int reg1, int reg2, int num) {
    regArr[reg1] = regArr[reg2] + num;
    return regArr[reg1];
}

int ALU::sub(int regArr[], int reg1, int reg2, int reg3) {
    regArr[reg1] = regArr[reg2] - regArr[reg3];
    return regArr[reg1];
}

int ALU::mul(int regArr[], int reg1, int reg2, int reg3) {
    regArr[reg1] = regArr[reg2] * regArr[reg3];
    return regArr[reg1];
}

int ALU::bitwise_and(int regArr[], int reg1, int reg2) {
    return regArr[reg1] & regArr[reg2];
}

int ALU::bitwise_or(int regArr[], int reg1, int reg2) {
    return regArr[reg1] | regArr[reg2];
}

int ALU::sll(int regArr[], int reg1, int reg2, int samt) {
    return regArr[reg1] = regArr[reg2] << samt;
}

int ALU::srl(int regArr[], int reg1, int reg2, int samt) {
    regArr[reg1] = static_cast<unsigned int>(regArr[reg2]) >> samt;
    return regArr[reg1];
}

std::string ALU::lw(std::string regArr[], int reg1) {
    return regArr[reg1];
}

void ALU::sw(std::string regArr[], int reg1, std::string str) {
    regArr[reg1] = str;
}





