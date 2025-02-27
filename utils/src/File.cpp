/**
 * @file File.cpp
 * @brief Implementation of file system utility functions
 * @author Your Name
 * @date February 27, 2025
 * 
 * This file implements the utility functions declared in File.hpp
 * for performing common file system operations. It uses the C++17
 * filesystem library to provide platform-independent file handling.
 */

 #include "File.hpp"
 #include <fstream>
 #include <iostream>
 #include <filesystem>
 
 // Namespace alias for the filesystem library to improve code readability
 namespace fs = std::filesystem;
 
 namespace FileUtils {
 
 /**
  * @brief Checks if a file exists in the file system
  * 
  * Uses the C++17 filesystem library to check for file existence.
  * 
  * @param filename Path to the file to check
  * @return true if the file exists, false otherwise
  */
 bool fileExists(const std::string& filename) {
     return fs::exists(filename);
 }
 
 /**
  * @brief Creates all necessary directories for a given file path
  * 
  * This function extracts the parent path from the provided file path
  * and creates all directories in that path recursively if they don't exist.
  * 
  * @param path Path containing the directories to create
  * @return true if directories were created successfully or already existed,
  *         false if an error occurred during directory creation
  * 
  * @note Error messages are output to stderr if an exception occurs during directory creation
  */
 bool createDirectories(const std::string& path) {
     try {
         // Extract the parent directory path from the full file path
         fs::path dirPath = fs::path(path).parent_path();
         
         // Only create directories if the path isn't empty and doesn't already exist
         if (!dirPath.empty() && !fs::exists(dirPath)) {
             fs::create_directories(dirPath);
         }
         return true;
     } catch (const std::exception& e) {
         // Log any exceptions that occur during directory creation
         std::cerr << "Error creating directories: " << e.what() << std::endl;
         return false;
     }
 }
 
 /**
  * @brief Creates a file if it doesn't already exist
  * 
  * This function will first check if the file exists, and if not, it will:
  * 1. Create any necessary parent directories
  * 2. Create an empty file at the specified path
  * 
  * @param filename Path to the file to create
  * @return true if the file exists after the operation (either it already existed or was successfully created),
  *         false if the file could not be created
  * 
  * @note Error messages are output to stderr if the file cannot be created
  */
 bool createFileIfNotExists(const std::string& filename) {
     // If the file already exists, no need to create it
     if (fileExists(filename)) {
         return true;
     }
     
     // Create parent directories if needed
     if (!createDirectories(filename)) {
         return false;
     }
     
     // Create the file by opening it in output mode
     std::ofstream file(filename);
     if (!file.is_open()) {
         std::cerr << "Error creating file: " << filename << std::endl;
         return false;
     }
     
     // Close the file to flush the buffer and release resources
     file.close();
     return true;
 }
 
 /**
  * @brief Reads the entire contents of a file into a string
  * 
  * This function:
  * 1. Checks if the file exists
  * 2. Opens the file for reading
  * 3. Reads the entire content into a string using stream iterators
  * 
  * @param filename Path to the file to read
  * @return String containing the file contents if successful,
  *         empty string if the file doesn't exist or couldn't be read
  * 
  * @note Error messages are output to stderr if the file cannot be read
  */
 std::string readFile(const std::string& filename) {
     // Check if the file exists before attempting to read
     if (!fileExists(filename)) {
         std::cerr << "File does not exist: " << filename << std::endl;
         return "";
     }
     
     // Open the file for reading
     std::ifstream file(filename);
     if (!file.is_open()) {
         std::cerr << "Error opening file: " << filename << std::endl;
         return "";
     }
     
     // Read the entire file content into a string using stream iterators
     // This is more efficient than reading line by line for most use cases
     std::string content((std::istreambuf_iterator<char>(file)),
                         (std::istreambuf_iterator<char>()));
     file.close();
     
     return content;
 }
 
 /**
  * @brief Writes string content to a file
  * 
  * This function will:
  * 1. Create any necessary parent directories
  * 2. Open the file for writing (truncating any existing content)
  * 3. Write the provided string content to the file
  * 
  * @param filename Path to the file to write
  * @param content String data to write to the file
  * @return true if the write operation was successful,
  *         false if the file couldn't be opened or written to
  * 
  * @note Error messages are output to stderr if the file cannot be written to
  */
 bool writeFile(const std::string& filename, const std::string& content) {
     // Create parent directories if needed
     if (!createDirectories(filename)) {
         return false;
     }
     
     // Open the file for writing (this will truncate any existing content)
     std::ofstream file(filename);
     if (!file.is_open()) {
         std::cerr << "Error opening file for writing: " << filename << std::endl;
         return false;
     }
     
     // Write the content to the file
     file << content;
     
     // Check if any errors occurred during writing
     if (file.fail()) {
         std::cerr << "Error writing to file: " << filename << std::endl;
         file.close();
         return false;
     }
     
     // Close the file to flush the buffer and release resources
     file.close();
     return true;
 }
 
 /**
  * @brief Deletes a file from the file system
  * 
  * This function:
  * 1. Checks if the file exists
  * 2. Attempts to remove the file using the filesystem library
  * 
  * @param filename Path to the file to delete
  * @return true if the file was successfully deleted or didn't exist,
  *         false if the file couldn't be deleted
  * 
  * @note Error messages are output to stderr if an exception occurs during file deletion
  */
 bool deleteFile(const std::string& filename) {
     // If the file doesn't exist, consider the deletion successful
     if (!fileExists(filename)) {
         return true;  // File already doesn't exist
     }
     
     try {
         // Attempt to remove the file
         fs::remove(filename);
         return true;
     } catch (const std::exception& e) {
         // Log any exceptions that occur during file deletion
         std::cerr << "Error deleting file: " << e.what() << std::endl;
         return false;
     }
 }
 
 } // namespace FileUtils