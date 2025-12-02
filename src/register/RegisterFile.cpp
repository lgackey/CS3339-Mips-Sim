#include "RegisterFile.h"
#include <bitset>
#include <cstdint>
#include <iomanip>
#include <iostream>

//The register that holds all the array names
const std::string regNames[32] = {"zero", "at", "v0", "v1", "a0", "a1", "a2", "a3",
                                "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
                                "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
                                "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra"};

//Read a register file
int RegisterFile::read(int regNum) const {
    if (regNum < 0 || regNum >= 32) {
        throw std::out_of_range("Register index out of range (0-31)");
    }
    return regArr[regNum];
}

// Write a value to a register (except zero)
int RegisterFile::write(int regNum, int value) {
    if (regNum < 0 || regNum >= 32) return INT_MIN; // $0 immutable, others protected by bounds
    regArr[regNum] = value;

    return value;
}

//code to convert an int to binary
std::bitset<32> RegisterFile::makeBinary(int n) const {
    uint32_t temp_bit_value;
    memcpy(&temp_bit_value, &n, sizeof(temp_bit_value));
    std::bitset<32> binary_form(temp_bit_value);
    return binary_form;
}

// Print all registers (useful for debug mode)
void RegisterFile::print() const {
    std::cout << "Register File State:" << std::endl;
    std::cout << std::setw(10) << std::left << "Name" << std::setw(15)
    << "Value" << std::setw(15) << "Binary Value" << std::endl;
    for (int i = 0; i < 32; ++i) {
        std::cout << std::setw(10) << std::left << regNames[i] << std::setw(15)
        << regArr[i] << std::setw(15) << makeBinary(regArr[i]) << std::endl;
    }
}
