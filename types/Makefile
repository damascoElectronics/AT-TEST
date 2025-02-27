# Makefile for types module

# Variables
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = ../obj/types

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Include paths for headers
INCLUDES = -I$(INC_DIR) -I../func/inc -I../utils/inc -I../deps/include

# Build all objects
all: $(OBJS)

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean generated files
clean:
	rm -f $(OBJ_DIR)/*.o

.PHONY: all clean