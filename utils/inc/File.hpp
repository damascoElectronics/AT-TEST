#ifndef FILE_HPP
#define FILE_HPP

#include <string>

namespace FileUtils {
    // Check if a file exists
    bool fileExists(const std::string& filename);
    
    // Create a file if it doesn't exist
    bool createFileIfNotExists(const std::string& filename);
    
    // Create necessary directories for a file path
    bool createDirectories(const std::string& path);
    
    // Read entire content of a file as string
    std::string readFile(const std::string& filename);
    
    // Write string content to a file
    bool writeFile(const std::string& filename, const std::string& content);
    
    // Delete a file
    bool deleteFile(const std::string& filename);
}

#endif // FILE_HPP