#pragma once
#ifndef REGISTERFILE_H
#define REGISTERFILE_H

#include <array>
#include <iostream>
#include <stdexcept>


class RegisterFile {
private:
    std::array<int, 32> regArr; // 32 general-purpose registers


public:
    RegisterFile();
    int read(int regNum) const;
    void write(int regNum, int value);
    // Reset all registers to 0
    void reset();

    // Print all registers (for debug mode)
    void print() const;
};

#endif