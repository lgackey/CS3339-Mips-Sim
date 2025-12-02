CXX = g++
CXXFLAGS = -Wall -g


TestParser: Parser.o TestParser.cpp
	$(CXX) $(CXXFLAGS) Parser.o TestParser.cpp

Parser.o: Parser.h Parser.cpp
	$(CXX) $(CXXFLAGS) -c Parser.cpp

