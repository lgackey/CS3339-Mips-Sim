#include "ALU.h"

int ALU::add(int a, int b) { return a + b; }
int ALU::sub(int a, int b) { return a - b; }
int ALU::mul(int a, int b) { return a * b; }
int ALU::bitwise_and(int a, int b) { return a & b; }
int ALU::bitwise_or(int a, int b) { return a | b; }
int ALU::sll(int value, int shamt) { return value << shamt; }
int ALU::srl(int value, int shamt) { return static_cast<unsigned int>(value) >> shamt; }
