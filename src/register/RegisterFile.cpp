#include "RegisterFile.h"
#include <bitset>
#include <cstdint>


const std::string regNames[32] = {"zero", "at", "v0", "v1", "a0", "a1", "a2", "a3",
                                "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
                                "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
                                "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra"};

RegisterFile::RegisterFile() {
    regArr.fill(0); // initialize all registers to 0
}

int RegisterFile::read(int regNum) const {
    if (regNum < 0 || regNum >= 32) {
        throw std::out_of_range("Register index out of range (0-31)");
    }
    return regArr[regNum];
}

// Write a value to a register (except $0)
void RegisterFile::write(int regNum, int value) {
    if (regNum <= 0 || regNum >= 32) return; // $0 immutable, others protected by bounds
    regArr[regNum] = value;
}

// Reset all registers to 0
void RegisterFile::reset() {
    regArr.fill(0);
}

//code to convert an int to binary
std::bitset<32> makeBinary(int n) {
    uint32_t temp_bit_value;
    memcpy(&temp_bit_value, &n, sizeof(temp_bit_value));
    std::bitset<32> binary_form(temp_bit_value);
    return binary_form;
}

// Print all registers (useful for debug mode)
void RegisterFile::print() const {
    std::cout << "Register File State:" << std::endl;
    std::cout << "Name\tValue\tBinary Value" << std::endl;
    for (int i = 0; i < 32; ++i) {
        std::cout << regNames[i] << "\t" << regArr[i] << "\t" << makeBinary(regArr[i]) << std::endl;
    }
}