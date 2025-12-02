#pragma once
#ifndef PIPELINE_H
#define PIPELINE_H

#include <string>
#include "../register/RegisterFile.h"
#include "../alu/ALU.h"
#include "../memory/Memory.h"
#include "../control/ControlUnit.h"
#include "../parser/Parser.h"

class ControlUnit; // forward declaration in case the full definition isn't available here

//  Pipeline register structures

struct IF_ID_Register {
    std::string opcode;
    int rs, rt, rd;
    int immediate;
    int address;   // for J-type
    bool isLabel;  // internal flag
    int pc = 0;
};

struct ID_EX_Register {
    std::string opcode;
    int rsVal = 0;
    int rtVal = 0;
    int rd = 0;
    int immediate = 0;
    ControlSignals signals; // Control signals for this instruction
};

struct EX_MEM_Register {
    int aluResult = 0;
    int rtVal = 0; // for SW
    int rd = 0;
    ControlSignals signals;
};

struct MEM_WB_Register {
    int writeData = 0;
    int rd = 0;
    ControlSignals signals;
};

//  Pipeline class
class Pipeline {
private:
    RegisterFile& rf;
    ALU& alu;
    Memory& mem;
    ControlUnit* controlUnit = nullptr;

    // Pipeline registers
    IF_ID_Register if_id;
    ID_EX_Register id_ex;
    EX_MEM_Register ex_mem;
    MEM_WB_Register mem_wb;

    bool is_current_instruction_jump;
    bool is_label;

public:
    // Constructor
    Pipeline(RegisterFile& rf_, ALU& alu_, Memory& mem_, ControlUnit* ctrl_);

    // Pipeline stages
    void fetch(const Instruction instruction, int pc);
    void decode();
    void execute();
    ControlSignals memoryAccess();
    void writeBack();

    // Optional: helper to print pipeline state for debugging
    void printPipelineState() const;
    bool is_jump_instruction();
    bool get_is_label();

};

#endif