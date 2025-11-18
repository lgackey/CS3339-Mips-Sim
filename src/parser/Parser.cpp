#include "Parser.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

// Helper to trim whitespace
static std::string trim(const std::string& s) {
    auto start = s.find_first_not_of(" \t");
    auto end = s.find_last_not_of(" \t");
    if (start == std::string::npos) return "";
    return s.substr(start, end - start + 1);
}

// Remove comments (# or //)
static std::string stripComments(const std::string& line) {
    std::string cleaned = line;

    // Remove '#' comments
    auto hashPos = cleaned.find('#');
    if (hashPos != std::string::npos)
        cleaned = cleaned.substr(0, hashPos);

    // Remove '//' comments
    auto slashPos = cleaned.find("//");
    if (slashPos != std::string::npos)
        cleaned = cleaned.substr(0, slashPos);

    return trim(cleaned);
}


using namespace std;



std::vector<Instruction> Parser::parseFile(const std::string& filename) {
    std::vector<Instruction> instructions;
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Failed to open file: " << filename << "\n";
        return instructions;
    }

    std::string line;
    while (std::getline(file, line)) {

         // ---- NEW: clean line ----
        std::string cleaned = stripComments(line);
        cleaned = trim(cleaned);

        if (cleaned.empty())
            continue;  // Skip blank/comment-only lines

        std::istringstream iss(cleaned);
        std::string opcode;
        int rs = 0, rt = 0, rd = 0, imm = 0;
        iss >> opcode; // simple placeholder parsing
        // Normalize opcode (ADD, SUB, LW, SW, etc.)
        std::transform(opcode.begin(), opcode.end(), opcode.begin(), ::toupper);
   
       

        // parse based on opcode
if (opcode == "ADDI") {
    // expected: addi rt, rs, imm
    std::string rt_str, rs_str;
    if (!(iss >> rt_str)) {
        std::cerr << "Parser error: missing rt for ADDI in line: " << cleaned << "\n";
    } else {
        // remove possible trailing commas
        if (rt_str.back() == ',') rt_str.pop_back();
        iss >> rs_str;
        if (!rs_str.empty() && rs_str.back() == ',') rs_str.pop_back();
        iss >> imm;

       

        rt = getRegisterNumber(rt_str);
        rs = getRegisterNumber(rs_str);
    }
}

else if (opcode == "ADD" || opcode == "SUB" || opcode == "AND" ||
         opcode == "OR"  || opcode == "SLL" || opcode == "SRL") {
    // expected: opcode rd, rs, rt
    std::string rd_str, rs_str, rt_str;
    if (!(iss >> rd_str >> rs_str >> rt_str)) {
        std::cerr << "Parser error: missing registers for " << opcode << " in line: " << cleaned << "\n";
    } else {
        // strip commas
        if (rd_str.back() == ',') rd_str.pop_back();
        if (rs_str.back() == ',') rs_str.pop_back();
        if (rt_str.back() == ',') rt_str.pop_back();

        rd = getRegisterNumber(rd_str);
        rs = getRegisterNumber(rs_str);
        rt = getRegisterNumber(rt_str);
    }
}

else if (opcode == "LW" || opcode == "SW") {
    // I-type memory parsing
    std::string rt_str, mem_str;
    if (!(iss >> rt_str >> mem_str)) {
        std::cerr << "Parser error: missing operands for " << opcode << " in line: " << cleaned << "\n";
    } else {
        if (rt_str.back() == ',') rt_str.pop_back();
        rt = getRegisterNumber(rt_str);

        size_t lp = mem_str.find('(');
        size_t rp = mem_str.find(')');
        if (lp != std::string::npos && rp != std::string::npos && rp > lp) {
            std::string offset_str = mem_str.substr(0, lp);
            std::string base_str   = mem_str.substr(lp + 1, rp - lp - 1);
            try { imm = std::stoi(offset_str); } catch(...) { imm = 0; }
            rs = getRegisterNumber(base_str);
        } else {
            std::cerr << "Parser error: malformed memory operand in line: " << cleaned << "\n";
        }
    }
} 
else {
    // fallback: keep old placeholder parsing for now
    iss >> rd >> rs >> rt;
}

        // Store parsed instruction
        instructions.push_back({opcode, rs, rt, rd, imm});
    }

    return instructions;
}
