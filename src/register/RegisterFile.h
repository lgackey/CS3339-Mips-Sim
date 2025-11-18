#pragma once
#include <array>

class RegisterFile {
private:
    std::array<int, 32> regs; // 32 general-purpose registers

public:
    RegisterFile();
    int read(int regNum) const;
    void write(int regNum, int value);
};
