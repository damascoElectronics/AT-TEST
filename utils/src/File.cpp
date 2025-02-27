#include "File.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

namespace FileUtils {

bool fileExists(const std::string& filename) {
    return fs::exists(filename);
}

bool createDirectories(const std::string& path) {
    try {
        fs::path dirPath = fs::path(path).parent_path();
        if (!dirPath.empty() && !fs::exists(dirPath)) {
            fs::create_directories(dirPath);
        }
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error creating directories: " << e.what() << std::endl;
        return false;
    }
}

bool createFileIfNotExists(const std::string& filename) {
    if (fileExists(filename)) {
        return true;
    }
    
    if (!createDirectories(filename)) {
        return false;
    }
    
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error creating file: " << filename << std::endl;
        return false;
    }
    
    file.close();
    return true;
}

std::string readFile(const std::string& filename) {
    if (!fileExists(filename)) {
        std::cerr << "File does not exist: " << filename << std::endl;
        return "";
    }
    
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return "";
    }
    
    std::string content((std::istreambuf_iterator<char>(file)),
                        (std::istreambuf_iterator<char>()));
    file.close();
    
    return content;
}

bool writeFile(const std::string& filename, const std::string& content) {
    if (!createDirectories(filename)) {
        return false;
    }
    
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return false;
    }
    
    file << content;
    
    if (file.fail()) {
        std::cerr << "Error writing to file: " << filename << std::endl;
        file.close();
        return false;
    }
    
    file.close();
    return true;
}

bool deleteFile(const std::string& filename) {
    if (!fileExists(filename)) {
        return true;  // File already doesn't exist
    }
    
    try {
        fs::remove(filename);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error deleting file: " << e.what() << std::endl;
        return false;
    }
}

} // namespace FileUtils