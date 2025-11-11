#include "Memory.h"

Memory::Memory(int size) {
    mem.resize(size, 0); // initialize all memory to 0
}

int Memory::loadWord(int address) const {
    if (address < 0 || address >= mem.size()) {
        throw std::out_of_range("Memory read out of bounds");
    }
    return mem[address];
}

void Memory::storeWord(int address, int value) {
    if (address < 0 || address >= mem.size()) {
        throw std::out_of_range("Memory write out of bounds");
    }
    mem[address] = value;
}
