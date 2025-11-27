#pragma once
#ifndef MEMORY_H
#define MEMORY_H

#include <vector>
#include <iostream>
#include <stdexcept>

class Memory {
private:
    std::vector<int> mem; // Memory represented as a vector of integers

public:
    Memory(int size = 1024);   // default 1024 words
    int loadWord(int address) const;
    void storeWord(int address, int value);
    // Reset all memory to 0
    void reset();

    // Print memory contents (for debug mode)
    void print() const;
};

#endif