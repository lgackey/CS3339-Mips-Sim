#pragma once
#include <vector>
#include <iostream>
#include <stdexcept>
#include <cstdint>

class Memory {
private:
    std::vector<uint32_t> memoryVec; // Memory represented as a vector of integers
    int size;

public:
    Memory () : size(1024) , memoryVec(1024,0) {}
    Memory(int s): size(s), memoryVec(s,0) {}   // default 1024 words
    int LW(int address) const;
    void SW(int address, int value);
    // Reset all memory to 0
    void reset();
    void memResize(int s);

    // Print memory contents (for debug mode)
    void print() const;
};
