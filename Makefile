CC := g++
CFLAGS := -g -std=c++11
exe = bdd
path = src

all:$(path)/main.cpp $(path)/BDD.hpp
	@$(CC) $(path)/main.cpp -o $(exe) $(CFLAGS)

clean:
	@rm -rf *.o *.dSYM $(exe)

