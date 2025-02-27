# Main Makefile for Library Management System
# This unified makefile handles both the main program and all submodules

# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

# Directory structure
OBJ_DIR = obj
BIN_DIR = bin
DATA_DIR = data
TEST_DIR = test
TYPES_DIR = types
UTILS_DIR = utils
FUNC_DIR = func

# Build the main program and all modules
all: directories modules main link

# Create all necessary directories
directories:
	mkdir -p $(OBJ_DIR)/$(TYPES_DIR)
	mkdir -p $(OBJ_DIR)/$(UTILS_DIR)
	mkdir -p $(OBJ_DIR)/$(FUNC_DIR)
	mkdir -p $(OBJ_DIR)/main
	mkdir -p $(BIN_DIR)
	mkdir -p $(DATA_DIR)

# Build all the modules
modules: build-types build-utils build-func

# Types module compilation
build-types:
	$(MAKE) -C $(TYPES_DIR)

# Utils module compilation
build-utils:
	$(MAKE) -C $(UTILS_DIR)

# Func module compilation
build-func:
	$(MAKE) -C $(FUNC_DIR)

# Main application compilation
main: $(OBJ_DIR)/main/main.o

# Compile the main.cpp file
$(OBJ_DIR)/main/main.o: main.cpp
	$(CXX) $(CXXFLAGS) -Itypes/inc -Ifunc/inc -Iutils/inc -Ideps/include -c $< -o $@

# Link everything into the final executable
link: $(BIN_DIR)/library_management_system

# Rule to link all object files into the executable
$(BIN_DIR)/library_management_system:
	$(CXX) $(CXXFLAGS) $(OBJ_DIR)/$(TYPES_DIR)/*.o $(OBJ_DIR)/$(UTILS_DIR)/*.o $(OBJ_DIR)/$(FUNC_DIR)/*.o $(OBJ_DIR)/main/*.o -o $@

# Clean up all generated files
clean:
	$(MAKE) -C $(TYPES_DIR) clean
	$(MAKE) -C $(UTILS_DIR) clean
	$(MAKE) -C $(FUNC_DIR) clean
	rm -f $(OBJ_DIR)/main/*.o
	rm -f $(BIN_DIR)/*

# Run tests with input from test directory
test: all
	$(BIN_DIR)/library_management_system < $(TEST_DIR)/test_input.txt

# For proper dependency handling
.PHONY: all directories modules main link clean test build-types build-utils build-func