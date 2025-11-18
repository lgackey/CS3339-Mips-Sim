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

         // ---- NEW: clean line ----
        std::string cleaned = stripComments(line);
        cleaned = trim(cleaned);

        if (cleaned.empty())
            continue;  // Skip blank/comment-only lines

        std::istringstream iss(cleaned);
        std::string opcode;
        int rs = 0, rt = 0, rd = 0, imm = 0;
        iss >> opcode >> rd >> rs >> rt; // simple placeholder parsing
        instructions.push_back({opcode, rs, rt, rd, imm});
    }

    return instructions;
}
*/