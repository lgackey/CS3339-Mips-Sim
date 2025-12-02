#include "Memory.h"
#include <bitset>
#include <cstdint>
#include <iomanip>
#include <iostream>

//Loads a word from memory
int Memory::LW(int address) const {
    if (address < 0 || address >= memoryVec.size()) {
        throw std::out_of_range("Memory read out of bounds");
    }
    return static_cast<int>(memoryVec[address]);
}

//Stores a word in memory
void Memory::SW(int address, int value) {
    if (address < 0 || address >= memoryVec.size()) {
        throw std::out_of_range("Memory write out of bounds");
    }
    memoryVec[address] = value;
}

//Makes an integer a binary number
std::bitset<32> makeBinary(int n) {
    uint32_t temp_bit_value;
    memcpy(&temp_bit_value, &n, sizeof(temp_bit_value));
    std::bitset<32> binary_form(temp_bit_value);
    return binary_form;
}

// Print memory contents
void Memory::print() const {
    std::cout << "Memory State: (only non-zero locations)" << std::endl;
    std::cout  << std::setw(15) << std::left << "Index" << std::setw(15)
    << "Mem location" << std::setw(15)<< "Value" << std::setw(15)
    << "Binary Value" << std::endl;
    for (size_t i = 0; i < memoryVec.size(); ++i) {
        if (memoryVec[i] != 0) // only print non-zero locations for brevity
            std::cout << std::setw(15) << std::left << i << std::setw(15)
        << 4*i << std::setw(15) << memoryVec[i] << std::setw(15)
        << makeBinary(memoryVec[i]) << std::endl;
    }
}
