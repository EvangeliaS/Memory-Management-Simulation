CXX = g++
CXXFLAGS = -Wall -g -std=c++11

all: G M

G: G.o process.o memory_tree.o memory_list.o
	$(CXX) $(CXXFLAGS) -o G G.o process.o memory_tree.o memory_list.o
	
M: M.o process.o memory_tree.o memory_list.o
	$(CXX) $(CXXFLAGS) -o M M.o process.o memory_tree.o memory_list.o

G.o: G.cpp process.hpp memory_tree.hpp memory_list.hpp
	$(CXX) $(CXXFLAGS) -c G.cpp

M.o: M.cpp process.hpp memory_tree.hpp memory_list.hpp
	$(CXX) $(CXXFLAGS) -c M.cpp

process.o: process.cpp process.hpp
	$(CXX) $(CXXFLAGS) -c process.cpp
	
memory_tree.o: memory_tree.cpp  memory_tree.hpp
	$(CXX) $(CXXFLAGS) -c memory_tree.cpp

memory_list.o: memory_list.cpp  memory_list.hpp
	$(CXX) $(CXXFLAGS) -c memory_list.cpp

clean:
	rm -f G M *o
