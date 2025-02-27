/**
 * @file File.hpp
 * @brief Header file declaring file system utility functions
 * @author Your Name
 * @date February 27, 2025
 * 
 * This file contains declarations for a collection of utility functions
 * that provide simplified access to common file system operations such as
 * checking file existence, reading/writing files, and managing directories.
 */

 #ifndef FILE_HPP
 #define FILE_HPP
 
 #include <string>
 
 /**
  * @namespace FileUtils
  * @brief Namespace containing utility functions for file operations
  * 
  * This namespace encapsulates several utility functions that simplify
  * common file system operations. These functions provide error handling
  * and a consistent interface for file management tasks across the application.
  */
 namespace FileUtils {
     /**
      * @brief Checks if a file exists in the file system
      * 
      * @param filename Path to the file to check
      * @return true if the file exists, false otherwise
      */
     bool fileExists(const std::string& filename);
     
     /**
      * @brief Creates a file if it doesn't already exist
      * 
      * This function will also create any necessary parent directories
      * in the file path if they don't exist.
      * 
      * @param filename Path to the file to create
      * @return true if the file exists after the operation (either it already existed or was successfully created),
      *         false if the file could not be created
      */
     bool createFileIfNotExists(const std::string& filename);
     
     /**
      * @brief Creates all necessary directories for a given file path
      * 
      * This function extracts the directory path from the provided file path
      * and creates all directories in that path if they don't already exist.
      * 
      * @param path Path containing the directories to create
      * @return true if directories were created successfully or already existed,
      *         false if an error occurred during directory creation
      */
     bool createDirectories(const std::string& path);
     
     /**
      * @brief Reads the entire contents of a file into a string
      * 
      * @param filename Path to the file to read
      * @return String containing the file contents if successful,
      *         empty string if the file doesn't exist or couldn't be read
      */
     std::string readFile(const std::string& filename);
     
     /**
      * @brief Writes string content to a file
      * 
      * This function will create any necessary parent directories
      * in the file path if they don't exist.
      * 
      * @param filename Path to the file to write
      * @param content String data to write to the file
      * @return true if the write operation was successful,
      *         false if the file couldn't be opened or written to
      */
     bool writeFile(const std::string& filename, const std::string& content);
     
     /**
      * @brief Deletes a file from the file system
      * 
      * @param filename Path to the file to delete
      * @return true if the file was successfully deleted or didn't exist,
      *         false if the file couldn't be deleted
      */
     bool deleteFile(const std::string& filename);
 }
 
 #endif // FILE_HPP