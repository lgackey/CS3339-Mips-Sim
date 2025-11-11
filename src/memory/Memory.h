#pragma once
#include <vector>
#include <stdexcept>

class Memory {
private:
    std::vector<int> mem; // Memory represented as a vector of integers

public:
    Memory(int size = 1024);   // default 1024 words
    int loadWord(int address) const;
    void storeWord(int address, int value);
};
