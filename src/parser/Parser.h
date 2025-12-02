#pragma once
#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <unordered_map>


struct Instruction {
    std::string opcode;
    int rs, rt, rd;
    int immediate;
    int address;   // for J-type
    bool isLabel;  // internal flag
};

class Parser {
public:
    std::vector<Instruction> parseFile(const std::string& filename);
    private:
    std::unordered_map<std::string, int> labelTable;

    int getRegisterNumber(const std::string& reg);
};


#endif