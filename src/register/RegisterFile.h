#pragma once

#include <array>

class RegisterFile {
private:
    std::array<int, 32> regArr; // 32 general-purpose registers

public:
    RegisterFile() {
        regArr.fill(0);
    };

    int read(int regNum) const;
    void write(int regNum, int value);

    // Print all registers (for debug mode)
    void print() const;
};
