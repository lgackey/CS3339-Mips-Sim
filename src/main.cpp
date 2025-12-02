#include <fstream>
#include <iostream>
#include "alu/ALU.h"
#include "register/RegisterFile.h"
#include "memory/Memory.h"
#include "pipeline/Pipeline.h"
#include "control/ControlUnit.h"
#include "parser/Parser.h"

#include <vector>
#include <iostream>



int main(int argc, char*argv[]) {

    /* check if the correct number of arguments have been passed; bail otherwise */
    if (argc < 3 || argc > 3) {
        std::cout << "Usage: " << std::endl;
        std::cout << "\t./mips_sim filename debug(true/false)" << std::endl;
        return 1;
    }

    std::string input_filename = argv[1];
    bool debug = argv[2];
    std::string output_filename = "MIPS_simulator_Output";
    //std::ofstream debug; we can maybe add this for the debug path

    Memory mem;
    RegisterFile reg;
    ALU alu(reg);

    Parser testParser = Parser();
    std::vector<Instruction> testVector = testParser.parseFile(input_filename);

    for(Instruction i: testVector) {
        std::cout << i.opcode << std::endl
        << "RS: " << i.rs << " RT: " << i.rt << " RD: " << i.rd << std::endl
        << "Immediate: " << i.immediate << std::endl
        << "Address: " << i.address << std::endl
        << "Is Label?: " << (i.isLabel ? "yes" : "no") << std::endl << std::endl;
    }

    std::cout << testParser.getLabelIndex("MAIN") << std::endl;

/*  OLD TESTS
    reg.write(8, 15);
    reg.write(9, 12);

    alu.ADD(10, 8, 9);
    alu.ADDI(11, 8, 200);
    alu.SUB(12, 8, 9);
    alu.MUL(13, 8, 9);
    alu.SLL(14, 8, 2);
    alu.SRL(15, 8, 2);
    alu.AND(24, 8, 9);
    alu.OR(25, 8, 9);

    reg.print();


    int a = 10, b = 5;

    std::cout << "ALU Tests:\n";
    try {
        std::cout << "ADD: " << alu.add(a,b) << "\n";
        std::cout << "SUB: " << alu.sub(a,b) << "\n";
    } catch (const std::overflow_error& e) {
        std::cerr << "ALU error: " << e.what() << "\n";
    }
    std::cout << "MUL: " << alu.mul(a,b) << "\n";
    std::cout << "AND: " << alu.bitwise_and(a,b) << "\n";
    std::cout << "OR: " << alu.bitwise_or(a,b) << "\n";
    std::cout << "SLL: " << alu.sll(a,2) << "\n";
    std::cout << "SRL: " << alu.srl(a,1) << "\n";

    // --- Register File test ---
    RegisterFile rf;
    rf.write(1, 42);
    rf.write(2, 100);

    std::cout << "\nRegister File Tests:\n";
    rf.print();  // debug print all registers


    // --- Memory test ---
    Memory mem(256); // 256 words of memory
    mem.storeWord(0, 123);
    mem.storeWord(1, 456);

    std::cout << "\nMemory Tests:\n";
    mem.print(); // debug print memory contents

    // After ALU, RegisterFile, Memory initialization
    Pipeline pipeline(rf, alu, mem);

    pipeline.fetch("ADD $3, $1, $2", 0);
    pipeline.decode();
    pipeline.execute();
    pipeline.memoryAccess();
    pipeline.writeBack();

    ControlUnit cu;
    try{
        auto signals = cu.generateSignals("ADD");
        cu.printSignals(signals);

        signals = cu.generateSignals("LW");
        cu.printSignals(signals);
    } catch (const std::invalid_argument& e) {
        std::cerr << "ControlUnit error: " << e.what() << "\n";
    }
    */

    return 0;
}