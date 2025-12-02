#pragma once

#include <vector>
#include <cstdint>
#include <bitset>

class Memory {
private:
    std::vector<uint32_t> memoryVec; // Memory represented as a vector of integers
    int size;

public:
    Memory () : size(1024) , memoryVec(1024,0) {}
    Memory(int s): size(s), memoryVec(s,0) {}   // default 1024 words

    int LW(int address) const;
    void SW(int address, int value);

    // Print memory contents (for debug mode)
    void print() const;
    std::bitset<32> makeBinary(int n) const;
};
