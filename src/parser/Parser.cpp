#include "Parser.h"
#include <climits>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <map>
#include <stdexcept>
#include <utility>

const std::map<std::string, int> regNames = {
    {"zero", 0}, {"at", 1}, {"v0", 2},
    {"v1", 3}, {"a0", 4}, {"a1", 5}, {"a2", 6}, {"a3", 7},
    {"t0", 8}, {"t1", 9}, {"t2", 10}, {"t3", 11}, {"t4", 12}, {"t5", 13}, {"t6", 14}, {"t7", 15},
    {"s0", 16}, {"s1", 17}, {"s2", 18}, {"s3", 19}, {"s4", 20}, {"s5", 21}, {"s6", 22}, {"s7", 23},
    {"t8", 24}, {"t9", 25}, {"k0", 26}, {"k1", 27}, {"gp", 28}, {"sp", 29}, {"fp", 30}, {"ra", 31}
};

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

    std::vector<pair<int, std::string>> jump_calls;
    std::vector<pair<int, std::string>> beq_calls;
    // vector with pairs, first value is location of jump call in instruction vector,
    // second value is string of label to jump to


    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Failed to open file: " << filename << "\n";
        return instructions;
    }

    int line_number = 0;
    std::string line;
    while (std::getline(file, line)) {

        // ---- NEW: clean line ----
        std::string cleaned = stripComments(line);
        cleaned = trim(cleaned);

        if (cleaned.empty())
            continue;  // Skip blank/comment-only lines

        std::istringstream iss(cleaned);
        std::string opcode;
        int rs = 0, rt = 0, rd = 0, imm = 0, addr = 0;
        bool is_label = false;
        iss >> opcode; // simple placeholder parsing
        // Normalize opcode (ADD, SUB, LW, SW, etc.)
        std::transform(opcode.begin(), opcode.end(), opcode.begin(), ::toupper);



        // parse based on opcode
        if (opcode == "ADDI") {
            // expected: addi rd, rs, imm
            std::string rd_str, rs_str;
            if (!(iss >> rd_str)) {
                std::cerr << "Parser error: missing rt for ADDI in line: " << cleaned << "\n";
            } else {
                // remove possible trailing commas
                if (rd_str.back() == ',') rs_str.pop_back();
                iss >> rs_str;
                if (!rs_str.empty() && rs_str.back() == ',') rs_str.pop_back();
                iss >> imm;



                rd = getRegisterNumber(rd_str);
                rs = getRegisterNumber(rs_str);

            }
        }

        else if (opcode == "ADD" || opcode == "SUB" || opcode == "AND" || opcode == "MUL" ||
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
        else if (opcode == "BEQ") {
            string rs_str, rt_str, label;
            if (!(iss >> rs_str >> rt_str >> label)) {
                cerr << "Parser error: missing operands for BEQ in line: " << cleaned << "\n";
            } else {
                if (rs_str.back() == ',') rs_str.pop_back();
                if (rt_str.back() == ',') rt_str.pop_back();
                rs = getRegisterNumber(rs_str);
                rt = getRegisterNumber(rt_str);
                rd = 0;
                beq_calls.push_back({line_number, label});
            }
        }
        else if (opcode == "J") {
            string label;
            if (!(iss >> label)) {
                cerr << "Parser error: missing operands for J in line: " << cleaned << "\n";
            } else {
                rs = 0;
                jump_calls.push_back({line_number, label});
            }
        }

        // else is label
        else if (opcode != "NOP") {

            // remove any : from opcode
            while(opcode.find(":") != string::npos) {
                opcode.erase(opcode.find(":"), opcode.find(":") + 1);
            }

            // fallback: keep old placeholder parsing for now
            iss >> rd >> rs >> rt;
            is_label = true;
            labelTable.insert({opcode, line_number});

        }

        // Store parsed instruction
        instructions.push_back({opcode, rs, rt, rd, imm, addr, is_label});
        line_number++;
    }

    for(pair<int, std::string> i : jump_calls) {
        instructions[i.first].rs = getLabelIndex(i.second);
    }

    for(pair<int, std::string> i : beq_calls) {
        instructions[i.first].rd = getLabelIndex(i.second);
    }

    return instructions;
}

int Parser::getRegisterNumber(const std::string& reg) {

    // get reg as string
    std::string str = reg;

    // remove any $
    while(str.find("$") != string::npos) {
        str.erase(str.find("$"), str.find("$") + 1);
    }

    // try to return as mapped key pair value of register names
    try {
        return regNames.at(str);
    }

    // if that fails, return as converted string
    catch (std::out_of_range){

        try {
            return stoi(str);
        }

        // if this fails, passed register is not a proper register
        catch(std::invalid_argument) {
            cout << "Given register is not a proper register!" << endl;
            cout << str << endl;
            return INT_MIN;
        }
    }
}

// get vector index of label
int Parser::getLabelIndex(const std::string& label) {
    std::string s = label;
    // https://www.geeksforgeeks.org/cpp/convert-cpp-string-to-uppercase/
    std::transform(s.begin(), s.end(), s.begin(),::toupper);
    try {
        return labelTable.at(s);
    }
    catch(std::out_of_range) {
        cout << "Invalid Label" << endl;
        return INT_MIN;
    }
}