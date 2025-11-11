#pragma once
#include <string>
#include <vector>

struct Instruction {
    std::string opcode;
    int rs, rt, rd;
    int immediate;
};

class Parser {
public:
    std::vector<Instruction> parseFile(const std::string& filename);
};
