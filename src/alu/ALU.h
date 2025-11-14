#ifndef ALU_H
#define ALU_H
#include <bitset>

class ALU {
public:
    int add(int regArr[], int reg1, int reg2, int reg3);
    int addi(int regArr[], int reg1, int reg2, int num);
    int sub(int regArr[], int reg1, int reg2, int reg3);
    int mul(int a, int b);

    int bitwise_and(int a, int b);
    int bitwise_or(int a, int b);

    int sll(int value, int shamt);
    int srl(int value, int shamt);

    void lw();
    void sw();

    std::bitset<32> makeBinary(int num);
    int makeInteger(std::bitset<32> binary);

};

#endif
