# Makefile for your project

# Compiler settings
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra

# Directories
SRC_DIR := src
BUILD_DIR := build

# Source files (add more if needed)
SRCS := $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Executable name
EXEC := my_program

# Input file
INPUT_FILE := inputs/input.csv

# Targets
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

run: $(EXEC)
	./$(EXEC) $(INPUT_FILE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(EXEC)

.PHONY: all clean run
