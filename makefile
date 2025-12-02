CXX = g++
CXXFLAGS = -Wall -g


main: build/ALU.o build/ControlUnit.o build/Memory.o build/Parser.o build/Pipeline.o build/RegisterFile.o src/main.cpp
	$(CXX) $(CXXFLAGS) build/ALU.o build/ControlUnit.o build/Memory.o build/Parser.o build/Pipeline.o build/RegisterFile.o src/main.cpp

build/ALU.o: src/alu/ALU.h src/alu/ALU.cpp
	$(CXX) $(CXXFLAGS) -c src/alu/ALU.cpp

build/ControlUnit.o: src/control/ControlUnit.h src/control/ControlUnit.cpp
	$(CXX) $(CXXFLAGS) -c src/control/ControlUnit.cpp

build/Memory.o: src/memory/Memory.h src/memory/Memory.cpp
	$(CXX) $(CXXFLAGS) -c src/memory/Memory.cpp

build/Parser.o: src/parser/Parser.h src/parser/Parser.cpp
	$(CXX) $(CXXFLAGS) -c src/parser/Parser.cpp

build/Pipeline.o: src/pipeline/Pipeline.h src/pipeline/Pipeline.cpp
	$(CXX) $(CXXFLAGS) -c src/pipeline/Pipeline.cpp

build/RegisterFile.o: src/register/RegisterFile.h src/register/RegisterFile.cpp
	$(CXX) $(CXXFLAGS) -c src/register/RegisterFile.cpp

TestParser: Parser.o TestParser.cpp
	$(CXX) $(CXXFLAGS) Parser.o TestParser.cpp

Parser.o: Parser.h Parser.cpp
	$(CXX) $(CXXFLAGS) -c Parser.cpp

cache_sim: cache_class.o main.cpp
	$(CXX) $(CXXFLAGS) cache_class.o main.cpp -o cache_sim.out

cache_class.o: cache_class.h cache_class.cpp
	$(CXX) $(CXXFLAGS) -c cache_class.cpp

