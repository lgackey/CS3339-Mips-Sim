#include "ControlUnit.h"

ControlSignals ControlUnit::generateSignals(const std::string& opcode) {
    ControlSignals signals = {};

    if (opcode == "ADD" || opcode == "SUB" || opcode == "MUL" ||
        opcode == "AND" || opcode == "OR" || opcode == "SLL" || opcode == "SRL") {
        signals.RegWrite = true;
        signals.MemRead = false;
        signals.MemWrite = false;
        signals.ALUSrc = false; // operand comes from register
        signals.MemToReg = false;
        signals.ALUOp = opcode;
    } 
    else if (opcode == "ADDI") {
        signals.RegWrite = true;
        signals.MemRead = false;
        signals.MemWrite = false;
        signals.ALUSrc = true; // operand comes from immediate
        signals.MemToReg = false;
        signals.ALUOp = "ADD";
    } 
    else if (opcode == "LW") {
        signals.RegWrite = true;
        signals.MemRead = true;
        signals.MemWrite = false;
        signals.ALUSrc = true; // base + offset
        signals.MemToReg = true;
        signals.ALUOp = "ADD";
    } 
    else if (opcode == "SW") {
        signals.RegWrite = false;
        signals.MemRead = false;
        signals.MemWrite = true;
        signals.ALUSrc = true; // base + offset
        signals.MemToReg = false;
        signals.ALUOp = "ADD";
    } 
    else if (opcode == "BEQ") {
        signals.RegWrite = false;
        signals.MemRead = false;
        signals.MemWrite = false;
        signals.ALUSrc = false;
        signals.MemToReg = false;
        signals.ALUOp = "SUB"; // for comparison
    } 
    else if (opcode == "J" || opcode == "NOP") {
        // do nothing
        signals.RegWrite = false;
        signals.MemRead = false;
        signals.MemWrite = false;
        signals.ALUSrc = false;
        signals.MemToReg = false;
        signals.ALUOp = "";
    }

    return signals;
}
