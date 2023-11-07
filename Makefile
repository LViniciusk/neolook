CC=g++
FLAGS=-Wall -Wextra -pedantic-errors -std=c++17

all : main.cpp
	$(CC) $(FLAGS) -g main.cpp -o main

clean:
	rm *.o