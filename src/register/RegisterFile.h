#pragma once

#include <array>
#include <bitset>

class RegisterFile {
private:
    std::array<int, 32> regArr; // 32 general-purpose registers

public:
    RegisterFile() {
        regArr.fill(0);
    };

    int read(int regNum) const;
    int write(int regNum, int value);
    std::bitset<32> makeBinary(int n) const;
    // Print all registers (for debug mode)
    void print() const;
};
