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

// Reset all memory to 0
void Memory::reset() {
    std::fill(mem.begin(), mem.end(), 0);
}

// Print memory contents (for debug mode)
void Memory::print() const {
    std::cout << "Memory State:\n";
    for (size_t i = 0; i < mem.size(); ++i) {
        if (mem[i] != 0) // only print non-zero locations for brevity
            std::cout << "Address " << i << ": " << mem[i] << "\n";
    }
}