#include "Pipeline.h"

class RegisterFile;
class ALU;
class Memory;

#include <iostream>
#include <string>

Pipeline::Pipeline(RegisterFile& rf_, ALU& alu_, Memory& mem_)
    : rf(rf_), alu(alu_), mem(mem_) {
    controlUnit = //ControlUnit implementation 
    }

// Fetch stage: just store instruction in IF/ID
void Pipeline::fetch(const std::string& instruction, int pc) {
    if_id.instruction = instruction;
    if_id.pc = pc;
}

// Decode stage: placeholder decode using ControlUnit
void Pipeline::decode() {

    std::string instr = if_id.instruction;
    std::string opcode;

    std::size_t pos = instr.find(' ');
    if (pos == std::string::npos) {
        opcode = instr;
    } else {
        opcode = instr.substr(0, pos);
    }

    id_ex.opcode = opcode;

    
    id_ex.rsVal = 1;
    id_ex.rtVal = 2;
    id_ex.rd = 3;
    id_ex.immediate = 0;

    id_ex.isBranch = (opcode == "BEQ");
    id_ex.isJump   = (opcode == "J");

    // Generate control signals from opcode
    id_ex.signals = controlUnit.generateSignals(id_ex.opcode);

    std::cout << "Decoding instruction: " << if_id.instruction << "\n";
}

// Execute stage: call ALU according to control signals
void Pipeline::execute() {
    // Pass control signals and register IDs forward by default
    ex_mem.signals = id_ex.signals;
    ex_mem.rd = id_ex.rd;
    ex_mem.rtVal = id_ex.rtVal;

    ex_mem.isBranch = id_ex.isBranch;
    ex_mem.isJump   = id_ex.isJump;

    
    if (id_ex.opcode == "ADD") {
        ex_mem.aluResult = alu.add(id_ex.rsVal, id_ex.rtVal);
        std::cout << "Executing ADD: " << ex_mem.aluResult << "\n";
    } 
    else if (id_ex.opcode == "SUB" || id_ex.opcode == "BEQ") {
        
        ex_mem.aluResult = alu.sub(id_ex.rsVal, id_ex.rtVal);
        std::cout << "Executing SUB/BEQ compare: " << ex_mem.aluResult << "\n";
   
        if (id_ex.isBranch) {
            bool taken = (ex_mem.aluResult == 0);
            std::cout << "Branch (BEQ) " << (taken ? "TAKEN" : "NOT TAKEN") << "\n";
            
        }
        else if (id_ex.isJump) {
            
            ex_mem.aluResult = 0;
            std::cout << "Executing JUMP instruction\n";
           
    
        } else {
         
            ex_mem.aluResult = id_ex.rsVal;
            std::cout << "Executing (default): " << ex_mem.aluResult << "\n";
        }
        }
}

// Memory stage
void Pipeline::memoryAccess() {
    mem_wb.signals = ex_mem.signals;

    if (ex_mem.signals.MemRead) {
        mem_wb.writeData = mem.loadWord(ex_mem.aluResult);
    } else if (ex_mem.signals.MemWrite) {
        mem.storeWord(ex_mem.aluResult, ex_mem.rtVal);
        // For a store, nothing to write back
        mem_wb.writeData = 0;
    } else {
        // ALU-only instruction: forward aluResult
        mem_wb.writeData = ex_mem.aluResult;
    }

    mem_wb.rd = ex_mem.rd;
}

// WriteBack stage: write to register file if enabled
void Pipeline::writeBack() {
    if (mem_wb.signals.RegWrite) {
        rf.write(mem_wb.rd, mem_wb.writeData);
        std::cout << "WriteBack: Register " << mem_wb.rd
                  << " = " << mem_wb.writeData << "\n";
    } else {
        std::cout << "WriteBack: no register write\n";
    }
}

// Debug helper
void Pipeline::printPipelineState() const {
    std::cout << "IF/ID: instr=\"" << if_id.instruction
              << "\" pc=" << if_id.pc << "\n";

    std::cout << "ID/EX: opcode=" << id_ex.opcode
              << " rsVal=" << id_ex.rsVal
              << " rtVal=" << id_ex.rtVal
              << " rd=" << id_ex.rd
              << " imm=" << id_ex.immediate << "\n";

    std::cout << "EX/MEM: aluResult=" << ex_mem.aluResult
              << " rtVal=" << ex_mem.rtVal
              << " rd=" << ex_mem.rd << "\n";

    std::cout << "MEM/WB: writeData=" << mem_wb.writeData
              << " rd=" << mem_wb.rd << "\n";
}
