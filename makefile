CXX = g++
CXXFLAGS = -Wall -g

main: cache_class.o main.cpp
	$(CXX) cache_class.o main.cpp -o cache_sim

cache_sim: cache_class.o main.cpp
	$(CXX) $(CXXFLAGS) cache_class.o main.cpp -o cache_sim.out

cache_class.o: cache_class.h cache_class.cpp
	$(CXX) $(CXXFLAGS) -c cache_class.cpp
