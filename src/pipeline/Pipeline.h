#pragma once
#include <string>
#include "register/RegisterFile.h"
#include "alu/ALU.h"
#include "memory/Memory.h"
#include "ControlUnit.h"

// --- Pipeline register structures ---
struct IF_ID_Register {
    std::string instruction;
    int pc;
};

struct ID_EX_Register {
    std::string opcode;
    int rsVal, rtVal;
    int rd;
    int immediate;
    ControlSignals signals; // Control signals for this instruction
};

struct EX_MEM_Register {
    int aluResult;
    int rtVal;  // for SW
    int rd;
    ControlSignals signals;
};

struct MEM_WB_Register {
    int writeData;
    int rd;
    ControlSignals signals;
};

// --- Pipeline class ---
class Pipeline {
private:
    RegisterFile& rf;
    ALU& alu;
    Memory& mem;
    ControlUnit controlUnit;

    // Pipeline registers
    IF_ID_Register if_id;
    ID_EX_Register id_ex;
    EX_MEM_Register ex_mem;
    MEM_WB_Register mem_wb;

public:
    // Constructor
    Pipeline(RegisterFile& rf_, ALU& alu_, Memory& mem_);

    // Pipeline stages
    void fetch(const std::string& instruction, int pc);
    void decode();
    void execute();
    void memoryAccess();
    void writeBack();

    // Optional: helper to print pipeline state for debugging
    void printPipelineState() const;
};
