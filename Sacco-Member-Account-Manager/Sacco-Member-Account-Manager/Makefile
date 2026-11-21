CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -pedantic -O2

HEADERS = Member.h HashTable.h AVLTree.h FileManager.h MemberOps.h Transactions.h SaccoOps.h Report.h

all: sacco tests

sacco: main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ main.cpp

tests: tests.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ tests.cpp

test: tests
	./tests

clean:
	rm -f sacco tests

.PHONY: all test clean
