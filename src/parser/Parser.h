#ifndef PARSER_H
#define PARSER_H

#include <string>
using namespace std;

class Parser {
public:

    enum instructions {
        ADD,
        ADDI,
        SUB,
        MUL,
        AND,
        OR,
        SLL,
        SRL,
        LW,
        SW,
        BEQ,
        J,
        NOP,
    };
};


#endif