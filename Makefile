CC=g++
FLAGS=-Wall -Wextra -pedantic-errors -std=c++17

SRC_DIR=src
INCLUDE_DIR=$(SRC_DIR)/includes
SYSTEM_DIR=$(SRC_DIR)/system
TADS_DIR=$(SRC_DIR)/tads
BIN_DIR=bin
BUILD_DIR=build

SYSTEM_SOURCES=$(wildcard $(SYSTEM_DIR)/*.cpp)
SYSTEM_OBJECTS=$(patsubst $(SYSTEM_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SYSTEM_SOURCES))

MAIN_SOURCE=$(SRC_DIR)/main.cpp
MAIN_OBJECT=$(BUILD_DIR)/main.o

all: $(BIN_DIR)/system

$(BIN_DIR)/system: $(SYSTEM_OBJECTS) $(MAIN_OBJECT)
	$(CC) $(FLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SYSTEM_DIR)/%.cpp $(INCLUDE_DIR)/%.h
	$(CC) $(FLAGS) -c $< -I $(INCLUDE_DIR) -o $@

$(MAIN_OBJECT): $(MAIN_SOURCE)
	$(CC) $(FLAGS) -c $< -I $(INCLUDE_DIR) -o $@

clean:
	rm -rf $(BIN_DIR)/* $(BUILD_DIR)/*

run: $(BIN_DIR)/system
	./$<

.PHONY: all clean run
