#include "Pipeline.h"
#include <iostream>

Pipeline::Pipeline(RegisterFile& rf_, ALU& alu_, Memory& mem_)
    : rf(rf_), alu(alu_), mem(mem_) {}

// Fetch stage: just store instruction in IF/ID
void Pipeline::fetch(const std::string& instruction, int pc) {
    if_id.instruction = instruction;
    if_id.pc = pc;
}

// Decode stage: for now just a dummy example
void Pipeline::decode() {
    // Normally we would parse opcode, registers, immediate
    std::cout << "Decoding instruction: " << if_id.instruction << "\n";
    // Placeholder values
    id_ex.opcode = "ADD";
    id_ex.rsVal = 1;
    id_ex.rtVal = 2;
    id_ex.rd = 3;
    id_ex.immediate = 0;

     // generate control signals
    id_ex.signals = controlUnit.generateSignals(id_ex.opcode);
}

// Execute stage: call ALU
void Pipeline::execute() {
    if (id_ex.opcode == "ADD") {
        ex_mem.aluResult = alu.add(id_ex.rsVal, id_ex.rtVal);
        ex_mem.rd = id_ex.rd;
        ex_mem.rtVal = id_ex.rtVal;
        std::cout << "Executing ADD: " << ex_mem.aluResult << "\n";
    }
}

// Memory stage: for now just pass values through
void Pipeline::memoryAccess() {
    ex_mem.signals = id_ex.signals;

     if (ex_mem.signals.MemRead)
        mem_wb.writeData = mem.loadWord(ex_mem.aluResult);
    else if (ex_mem.signals.MemWrite)
        mem.storeWord(ex_mem.aluResult, ex_mem.rtVal);
    else
        mem_wb.writeData = ex_mem.aluResult;

    mem_wb.rd = ex_mem.rd;
    mem_wb.signals = ex_mem.signals;
}

// WriteBack stage: write to register file
void Pipeline::writeBack() {
    rf.write(mem_wb.rd, mem_wb.writeData);
    std::cout << "WriteBack: Register " << mem_wb.rd << " = " << mem_wb.writeData << "\n";
}
