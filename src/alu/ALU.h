#ifndef ALU_H
#define ALU_H
#include <bitset>

class ALU {
public:
    int add(int regArr[], int reg1, int reg2, int reg3);
    int addi(int regArr[], int reg1, int reg2, int num);
    int sub(int regArr[], int reg1, int reg2, int reg3);
    int mul(int regArr[], int reg1, int reg2, int reg3);

    int bitwise_and(int a, int b);
    int bitwise_or(int a, int b);

    int sll(int regArr[], int reg1, int reg2, int samt);
    int srl(int regArr[], int reg1, int reg2, int samt);

    std::string lw(std::string regArr[], int reg);
    void sw(std::string regArr[], int reg1, std::string str);

    std::bitset<32> makeBinary(int num);
    int makeInteger(std::bitset<32> binary);

};

#endif
