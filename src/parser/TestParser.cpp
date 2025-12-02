#include <iostream>
#include "Parser.h"


using namespace std;

int main(int argc, char*argv[]) {

    Parser testParser = Parser();
    vector<Instruction> testVector = testParser.parseFile("../testinput.asm");

    cout << "working" << endl;
    for(Instruction i: testVector) {
        cout << i.opcode
        << i.rs << " " << i.rt << " " << i.rd << endl
        << i.immediate << endl
        << i.isLabel << endl;
    }

    cout << testVector[0].opcode << endl;
}