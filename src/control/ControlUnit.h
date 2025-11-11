#pragma once
#include <string>

struct ControlSignals {
    bool RegWrite;   // Write to register file
    bool MemRead;    // Read from memory
    bool MemWrite;   // Write to memory
    bool ALUSrc;     // ALU operand comes from immediate or register
    bool MemToReg;   // Write data comes from memory or ALU
    std::string ALUOp; // Which ALU operation: ADD, SUB, AND, OR, etc.
};

class ControlUnit {
public:
    ControlSignals generateSignals(const std::string& opcode);
};
