#include "Pipeline.h"

class RegisterFile;
class ALU;
class Memory;

#include <iostream>
#include <string>

Pipeline::Pipeline(RegisterFile& rf_, ALU& alu_, Memory& mem_, ControlUnit* ctrl_)
    : rf(rf_), alu(alu_), mem(mem_) {
    controlUnit = ctrl_; //ControlUnit implementation
    }

// Fetch stage: just store instruction in IF/ID
void Pipeline::fetch(const Instruction instruction, int pc) {
    if_id.opcode = instruction.opcode;
    if_id.rs = instruction.rs;
    if_id.rt = instruction.rt;
    if_id.rd = instruction.rd;
    if_id.immediate = instruction.immediate;
    if_id.address = instruction.address;   // for J-type
    if_id.isLabel = instruction.isLabel;
    if_id.pc = pc;
}

// Decode stage: placeholder decode using ControlUnit
void Pipeline::decode() {
    is_label = false;

    std::string instr = if_id.opcode;
    std::string opcode;

    std::size_t pos = instr.find(' ');
    if (pos == std::string::npos) {
        opcode = instr;
    } else {
        opcode = instr.substr(0, pos);
    }

    id_ex.opcode = opcode;

    // Placeholder: fake register and immediate values until you add a real parser
    id_ex.rsVal = if_id.rs;
    id_ex.rtVal = if_id.rt;
    id_ex.rd = if_id.rd;

    std::cout << id_ex.rd << " " << id_ex.rsVal << " " << id_ex.rtVal << std::endl;
    id_ex.immediate = if_id.immediate;

    if (id_ex.opcode == "ADD") {
        id_ex.signals = controlUnit->generateSignals(id_ex.opcode);
    }
    else if (id_ex.opcode == "ADDI") {
        id_ex.signals = controlUnit->generateSignals(id_ex.opcode);
    }
    else if (id_ex.opcode == "SUB") {
        id_ex.signals = controlUnit->generateSignals(id_ex.opcode);
    }
    else if(id_ex.opcode == "MUL") {
        id_ex.signals = controlUnit->generateSignals(id_ex.opcode);
    }
    else if(id_ex.opcode == "AND") {
        id_ex.signals = controlUnit->generateSignals(id_ex.opcode);
    }
    else if(id_ex.opcode == "OR") {
        id_ex.signals = controlUnit->generateSignals(id_ex.opcode);
    }
    else if(id_ex.opcode == "SLL") {
        id_ex.signals = controlUnit->generateSignals(id_ex.opcode);
    }
    else if(id_ex.opcode == "SRL") {
        id_ex.signals = controlUnit->generateSignals(id_ex.opcode);
    }
    else if(id_ex.opcode == "LW") {
        id_ex.signals = controlUnit->generateSignals(id_ex.opcode);
    }
    else if(id_ex.opcode == "SW") {
        id_ex.signals = controlUnit->generateSignals(id_ex.opcode);
    }
    else if(id_ex.opcode == "BEQ") {
        id_ex.signals = controlUnit->generateSignals(id_ex.opcode);
    }
    else if(id_ex.opcode == "J") {
        id_ex.signals = controlUnit->generateSignals(id_ex.opcode);
    }
    else if(id_ex.opcode == "NOP") {
        id_ex.signals = controlUnit->generateSignals(id_ex.opcode);
    }
    else {
        is_label = true;
        return;
    }

    std::cout << "Decoding instruction: " << if_id.opcode << "\n";
}

// Execute stage: call ALU according to control signals
void Pipeline::execute() {

    is_current_instruction_jump = false;
    // Pass control signals and register IDs forward by default
    ex_mem.signals = id_ex.signals;
    ex_mem.rd = id_ex.rd;
    ex_mem.rtVal = id_ex.rtVal;

    // Very simple example: use opcode to pick ALU op
    if (id_ex.opcode == "ADD") {
        ex_mem.aluResult = alu.ADD(id_ex.rd, id_ex.rsVal, id_ex.rtVal);
        std::cout << "Executing ADD: " << ex_mem.aluResult << "\n";
    }
    else if (id_ex.opcode == "ADDI") {
        std::cout << id_ex.immediate << std::endl;
        ex_mem.aluResult = alu.ADDI(id_ex.rd, id_ex.rsVal, id_ex.immediate);
        std::cout << "Executing ADDI: " << ex_mem.aluResult << "\n";
    }
    else if (id_ex.opcode == "SUB") {
        ex_mem.aluResult = alu.SUB(id_ex.rd, id_ex.rsVal, id_ex.rtVal);
        std::cout << "Executing SUB: " << ex_mem.aluResult << "\n";
    }
    else if(id_ex.opcode == "MUL") {
        ex_mem.aluResult = alu.MUL(id_ex.rd, id_ex.rsVal, id_ex.rtVal);
        std::cout << "Executing MUL: " << ex_mem.aluResult << "\n";
    }
    else if(id_ex.opcode == "AND") {
        ex_mem.aluResult = alu.AND(id_ex.rd, id_ex.rsVal, id_ex.rtVal);
        std::cout << "Executing AND: " << ex_mem.aluResult << "\n";
    }
    else if(id_ex.opcode == "OR") {
        ex_mem.aluResult = alu.OR(id_ex.rd, id_ex.rsVal, id_ex.rtVal);
        std::cout << "Executing OR: " << ex_mem.aluResult << "\n";
    }
    else if(id_ex.opcode == "SLL") {
        ex_mem.aluResult = alu.SLL(id_ex.rd, id_ex.rsVal, id_ex.rtVal);
        std::cout << "Executing SLL: " << ex_mem.aluResult << "\n";
    }
    else if(id_ex.opcode == "SRL") {
        ex_mem.aluResult = alu.SRL(id_ex.rd, id_ex.rsVal, id_ex.rtVal);
        std::cout << "Executing SRL: " << ex_mem.aluResult << "\n";
    }
    else if(id_ex.opcode == "LW") {
        ex_mem.aluResult = id_ex.rsVal;
    }
    else if(id_ex.opcode == "SW") {
        ex_mem.aluResult = id_ex.rsVal;
    }
    else if(id_ex.opcode == "BEQ") {
        if(id_ex.rsVal == id_ex.rtVal) {
            is_current_instruction_jump = true;
        }
    }
    else if(id_ex.opcode == "J") {
        is_current_instruction_jump = true;
    }
}

// Memory stage
ControlSignals Pipeline::memoryAccess() {
    mem_wb.signals = ex_mem.signals;

    if (ex_mem.signals.MemRead) {
        mem_wb.writeData = mem.LW(ex_mem.aluResult);
    } else if (ex_mem.signals.MemWrite) {
        mem.SW(ex_mem.aluResult, ex_mem.rtVal);
        // For a store, nothing to write back
        mem_wb.writeData = 0;
    } else {
        // ALU-only instruction: forward aluResult
        mem_wb.writeData = ex_mem.aluResult;
    }

    mem_wb.rd = ex_mem.rd;

    return mem_wb.signals;
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
    std::cout << "IF/ID: instr=\"" << if_id.opcode
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

    std::cout << std::endl;
}

bool Pipeline::is_jump_instruction() {
    return is_current_instruction_jump;
}

bool Pipeline::get_is_label() {
    return is_label;
}