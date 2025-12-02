CXX = g++
CXXFLAGS = -Wall -g


main: ALU.o ControlUnit.o Memory.o Parser.o Pipeline.o RegisterFile.o src/main.cpp
	$(CXX) $(CXXFLAGS) ALU.o ControlUnit.o Memory.o Parser.o Pipeline.o RegisterFile.o src/main.cpp -o "mips_sim"

ALU.o: src/alu/ALU.h src/alu/ALU.cpp
	$(CXX) $(CXXFLAGS) -c src/alu/ALU.cpp

ControlUnit.o: src/control/ControlUnit.h src/control/ControlUnit.cpp
	$(CXX) $(CXXFLAGS) -c src/control/ControlUnit.cpp

Memory.o: src/memory/Memory.h src/memory/Memory.cpp
	$(CXX) $(CXXFLAGS) -c src/memory/Memory.cpp

Parser.o: src/parser/Parser.h src/parser/Parser.cpp
	$(CXX) $(CXXFLAGS) -c src/parser/Parser.cpp

Pipeline.o: src/pipeline/Pipeline.h src/pipeline/Pipeline.cpp
	$(CXX) $(CXXFLAGS) -c src/pipeline/Pipeline.cpp

RegisterFile.o: src/register/RegisterFile.h src/register/RegisterFile.cpp
	$(CXX) $(CXXFLAGS) -c src/register/RegisterFile.cpp



