#include <iostream>
#include "Parser.h"


using namespace std;

int main(int argc, char*argv[]) {

    Parser testParser = Parser();
    vector<Instruction> testVector = testParser.parseFile("../testinput.asm");

    for(Instruction i: testVector) {
        cout << i.opcode << endl
        << "RS: " << i.rs << " RT: " << i.rt << " RD: " << i.rd << endl
        << "Immediate: " << i.immediate << endl
        << "Address: " << i.address << endl
        << "Is Label?: " << (i.isLabel ? "yes" : "no") << endl << endl;
    }

    cout << testParser.getLabelIndex("MAIN") << endl;
}