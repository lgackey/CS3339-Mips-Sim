#include "ALU.h"

#include <iostream>
#include <climits>

int ALU::add(int a, int b) {
    long long res = static_cast<long long>(a) + b;
    if (res > INT_MAX || res < INT_MIN) throw std::overflow_error("ALU overflow");
    return static_cast<int>(res);
}

int ALU::sub(int a, int b) {
    long long res = static_cast<long long>(a) - b;
    if (res > INT_MAX || res < INT_MIN) throw std::overflow_error("ALU overflow");
    return static_cast<int>(res);
}

int ALU::add(int a, int b) { return a + b; }
int ALU::sub(int a, int b) { return a - b; }
int ALU::mul(int a, int b) { return a * b; }
int ALU::bitwise_and(int a, int b) { return a & b; }
int ALU::bitwise_or(int a, int b) { return a | b; }
int ALU::sll(int value, int shamt) { return value << shamt; }
int ALU::srl(int value, int shamt) { return static_cast<unsigned int>(value) >> shamt; }
