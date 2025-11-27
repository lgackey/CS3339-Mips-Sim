#pragma once
#ifndef CONTROLUNIT_H
#define CONTROLUNIT_H

#include <string>
#include <iostream>
#include <stdexcept>

struct ControlSignals {
    bool RegWrite = false;   // Write to register file
    bool MemRead = false;    // Read from memory
    bool MemWrite = false;   // Write to memory
    bool ALUSrc = false;     // ALU operand comes from immediate or register
    bool MemToReg = false;   // Write data comes from memory or ALU
    std::string ALUOp = ""; // Which ALU operation: ADD, SUB, AND, OR, etc.
};

class ControlUnit {
public:
    ControlSignals generateSignals(const std::string& opcode);
    void printSignals(const ControlSignals& s) const; // debug
};

#endif