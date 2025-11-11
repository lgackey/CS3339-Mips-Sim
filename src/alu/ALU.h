#pragma once

class ALU {
public:
    int add(int a, int b);
    int sub(int a, int b);
    int mul(int a, int b);
    int bitwise_and(int a, int b);
    int bitwise_or(int a, int b);
    int sll(int value, int shamt);
    int srl(int value, int shamt);
};
