#include <fstream>
#include <iostream>
#include "alu/ALU.h"
#include "register/RegisterFile.h"
#include "memory/Memory.h"
#include "pipeline/Pipeline.h"
#include "control/ControlUnit.h"
#include "parser/Parser.h"

#include <sstream>
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
    bool debug = atoi(argv[2]);
    std::string output_filename = "MIPS_simulator_Output";
    std::ofstream output;

    Memory mem;
    RegisterFile reg;
    ALU alu(reg);
    ControlUnit* ctrl = new ControlUnit();
    Pipeline pipeline = Pipeline(reg, alu, mem, ctrl);

    Parser parser = Parser();
    std::vector<Instruction> instructions = parser.parseFile(input_filename);

    /*
    for(Instruction i: instructions) {
        std::cout << i.opcode << std::endl
        << "RS: " << i.rs << " RT: " << i.rt << " RD: " << i.rd << std::endl
        << "Immediate: " << i.immediate << std::endl
        << "Address: " << i.address << std::endl
        << "Is Label?: " << (i.isLabel ? "yes" : "no") << std::endl << std::endl;
    }
    */

    int pc = 0;
    for(int i = 0; i < instructions.size(); i++) {
        pipeline.fetch(instructions[i], pc);
        pipeline.decode();
        if(!pipeline.get_is_label()) {
            pipeline.execute();
            if(pipeline.is_jump_instruction()) {
                if(instructions[i].opcode == "J") {
                    i = instructions[i].rs;
                }
                if(instructions[i].opcode == "BEQ") {
                    i = instructions[i].rd;
                }
            }
            else {
                ControlSignals doWB = pipeline.memoryAccess();
                pipeline.writeBack();

                if(debug) {
                    pipeline.printPipelineState();
                    std::cout << std::endl;
                    ctrl->printSignals(doWB);
                    std::cout << std::endl;
                    reg.print();
                    std::cout << std::endl;
                    mem.print();
                    std::cout << std::endl;
                }
            }
            pc += 4;
        }
    }

    output.open(output_filename);

    std::cout << std::endl;
    reg.print();
    std::cout << std::endl;
    mem.print();

    output.close();



    return 0;
}