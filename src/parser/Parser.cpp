#include "Parser.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;


/*
std::vector<Instruction> Parser::parseFile(const std::string& filename) {
    std::vector<Instruction> instructions;
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Failed to open file: " << filename << "\n";
        return instructions;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string opcode;
        int rs = 0, rt = 0, rd = 0, imm = 0;
        iss >> opcode >> rd >> rs >> rt; // simple placeholder parsing
        instructions.push_back({opcode, rs, rt, rd, imm});
    }

    return instructions;
}
*/