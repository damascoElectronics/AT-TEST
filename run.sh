#!/bin/sh

# Library Management System Build and Run Script
# This script detects OS, checks for nlohmann_json library, 
# compiles the project, and runs the program.

# Text formatting
BOLD='\033[1m'
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Banner
echo  "${BOLD}${BLUE}================================${NC}"
echo  "${BOLD}${BLUE}  Library Management System     ${NC}"
echo  "${BOLD}${BLUE}  Build and Run Script          ${NC}"
echo  "${BOLD}${BLUE}================================${NC}"

# Function to detect the OS
detect_os() {
    echo "\n${BOLD}Detecting operating system...${NC}"
    
    case "$OSTYPE" in
        linux*)
            echo "${GREEN}Linux detected.${NC}"
            OS="linux"
            ;;
        darwin*)
            echo "${GREEN}macOS detected.${NC}"
            OS="macos"
            ;;
        msys*|cygwin*|mingw*)
            echo "${GREEN}Windows detected.${NC}"
            OS="windows"
            ;;
        *)
            echo "${YELLOW}Unknown OS. Will attempt to proceed anyway.${NC}"
            OS="unknown"
            ;;
    esac
}

# Function to check for required build tools
check_build_tools() {
    echo "\n${BOLD}Checking for required build tools...${NC}"
    
    # Check for make
    if command -v make > /dev/null 2>&1; then
        MAKE_PATH=$(which make)
        echo "${GREEN}make found: $MAKE_PATH${NC}"
        MAKE_COMMAND="make"
    elif [ -f "/usr/bin/make" ]; then
        echo "${GREEN}make found: /usr/bin/make${NC}"
        MAKE_COMMAND="/usr/bin/make"
    elif [ -f "/bin/make" ]; then
        echo "${GREEN}make found: /bin/make${NC}"
        MAKE_COMMAND="/bin/make"
    else
        echo "${RED}make not found. Please install make to compile the project.${NC}"
        if [ "$OS" = "linux" ]; then
            echo "${YELLOW}On most Linux distributions, you can install make with:${NC}"
            echo "  sudo apt-get install build-essential    (Debian/Ubuntu)"
            echo "  sudo yum install make                   (CentOS/RHEL)"
            echo "  sudo dnf install make                   (Fedora)"
        elif [ "$OS" = "macos" ]; then
            echo "${YELLOW}On macOS, you can install make with:${NC}"
            echo "  xcode-select --install"
        fi
        return 1
    fi
    
    # Check for g++
    if command -v g++ > /dev/null 2>&1; then
        CPP_PATH=$(which g++)
        echo "${GREEN}g++ found: $CPP_PATH${NC}"
    elif [ -f "/usr/bin/g++" ]; then
        echo "${GREEN}g++ found: /usr/bin/g++${NC}"
    else
        echo "${YELLOW}g++ may not be in PATH. Compilation might fail if g++ is not available.${NC}"
        if [ "$OS" = "linux" ]; then
            echo "${YELLOW}On most Linux distributions, you can install g++ with:${NC}"
            echo "  sudo apt-get install g++               (Debian/Ubuntu)"
            echo "  sudo yum install gcc-c++              (CentOS/RHEL)"
            echo "  sudo dnf install gcc-c++              (Fedora)"
        elif [ "$OS" = "macos" ]; then
            echo "${YELLOW}On macOS, you can install g++ with:${NC}"
            echo "  xcode-select --install"
        fi
    fi
    
    return 0
}

# Function to check and install nlohmann_json library
check_json_lib() {
    echo "\n${BOLD}Checking for nlohmann/json library...${NC}"
    
    # Create deps directory structure
    mkdir -p deps/include/nlohmann
    
    # Check if the JSON file already exists
    if [ -f "deps/include/nlohmann/json.hpp" ]; then
        echo "${GREEN}JSON library already installed in deps/include/nlohmann/json.hpp${NC}"
    else
        echo "${YELLOW}JSON library not found in deps. Downloading...${NC}"
        
        # Try to download the single-include JSON header
        if command -v curl > /dev/null 2>&1; then
            curl -s -o deps/include/nlohmann/json.hpp https://raw.githubusercontent.com/nlohmann/json/develop/single_include/nlohmann/json.hpp
            if [ $? -eq 0 ]; then
                echo "${GREEN}Successfully downloaded JSON library.${NC}"
            else
                echo "${RED}Failed to download JSON library with curl.${NC}"
                return 1
            fi
        elif command -v wget > /dev/null 2>&1; then
            wget -q -O deps/include/nlohmann/json.hpp https://raw.githubusercontent.com/nlohmann/json/develop/single_include/nlohmann/json.hpp
            if [ $? -eq 0 ]; then
                echo "${GREEN}Successfully downloaded JSON library.${NC}"
            else
                echo "${RED}Failed to download JSON library with wget.${NC}"
                return 1
            fi
        else
            echo "${RED}Neither curl nor wget found. Cannot download JSON library.${NC}"
            echo "${YELLOW}Please manually download the JSON library from:${NC}"
            echo "https://raw.githubusercontent.com/nlohmann/json/develop/single_include/nlohmann/json.hpp"
            echo "${YELLOW}and save it to deps/include/nlohmann/json.hpp${NC}"
            return 1
        fi
    fi
    
    return 0
}

# Function to compile the project
compile_project() {
    echo "\n${BOLD}Compiling project...${NC}"
    
    # Check if MAKE_COMMAND is set
    if [ -z "$MAKE_COMMAND" ]; then
        echo "${RED}Make command not found. Cannot compile project.${NC}"
        return 1
    fi
    
    # Clean and compile
    echo "${BLUE}Running make clean...${NC}"
    $MAKE_COMMAND clean || true  # Continue even if clean fails
    
    echo "${BLUE}Running make...${NC}"
    $MAKE_COMMAND
    
    if [ $? -eq 0 ]; then
        echo "${GREEN}Compilation successful!${NC}"
        return 0
    else
        echo "${RED}Compilation failed. See errors above.${NC}"
        return 1
    fi
}

# Function to run the program
run_program() {
    echo "\n${BOLD}Running Library Management System...${NC}"
    
    if [ -f "bin/library_management_system" ]; then
        echo  "\n${BLUE}Starting program...${NC}"
        echo  "${BOLD}${BLUE}================================${NC}"
        ./bin/library_management_system
    else
        echo "${RED}Executable not found. Compilation may have failed.${NC}"
        return 1
    fi
}

# Main execution flow
main() {
    detect_os
    check_build_tools
    
    if [ $? -ne 0 ]; then
        echo "${RED}Required build tools missing. Exiting.${NC}"
        exit 1
    fi
    
    check_json_lib
    
    if [ $? -ne 0 ]; then
        echo "${RED}Failed to set up JSON library. Exiting.${NC}"
        exit 1
    fi
    
    compile_project
    
    if [ $? -ne 0 ]; then
        echo "${RED}Compilation failed. Exiting.${NC}"
        exit 1
    fi
    
    # Ask if user wants to run the program
    echo "\n${BOLD}Do you want to run the program now? (y/n)${NC}"
    read answer
    
    case "$answer" in
        [Yy]*)
            run_program
            ;;
        *)
            echo "\n${BLUE}To run the program later, use:${NC}"
            echo "${BOLD}./run.sh run${NC}"
            ;;
    esac
}

# Allow running just a specific function
if [ "$1" = "run" ]; then
    run_program
    exit 0
fi

# Run the main function
main

echo  "\n${BOLD}${BLUE}================================${NC}"
echo  "${BOLD}${BLUE}  Script Completed              ${NC}"
echo  "${BOLD}${BLUE}================================${NC}"