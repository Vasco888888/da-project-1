# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra -Iinclude

# Directories
SRC_DIR = src
INC_DIR = include
BIN_DIR = bin
DATA_DIR = data

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
# Object files (currently just compiling directly to executable for simplicity, or we can use objects)
# TARGET = $(BIN_DIR)/best-route
TARGET = best-route # Keep it at root or in bin? bin/ is better.

all: $(BIN_DIR)/best-route

$(BIN_DIR)/best-route: $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(BIN_DIR)/best-route

clean:
	rm -f $(BIN_DIR)/best-route

.PHONY: all clean
