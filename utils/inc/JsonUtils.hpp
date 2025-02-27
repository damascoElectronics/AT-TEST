/**
 * @file JsonUtils.hpp
 * @brief Header file declaring JSON serialization and deserialization utilities
 * @author Your Name
 * @date February 27, 2025
 * 
 * This file contains declarations for utility functions that handle the conversion
 * between Book objects and JSON representations, as well as reading from and writing
 * to JSON files. These utilities serve as the data persistence layer for the
 * library management system.
 */

 #ifndef JSON_UTILS_HPP
 #define JSON_UTILS_HPP
 
 #include <string>
 #include <vector>
 #include "models.hpp"
 
 /**
  * @namespace JsonUtils
  * @brief Namespace containing utility functions for JSON operations
  * 
  * This namespace encapsulates functions for converting Book objects to and from JSON format,
  * as well as reading collections of books from JSON files and writing them back.
  * It serves as the serialization/deserialization layer of the application.
  */
 namespace JsonUtils {
     /**
      * @brief Reads a collection of Book objects from a JSON file
      * 
      * This function reads a JSON array from the specified file and converts each element
      * into a Book object. If the file doesn't exist, an empty file with a JSON array "[]"
      * will be created, and an empty vector will be returned.
      * 
      * @param filename Path to the JSON file to read
      * @return Vector of Book objects parsed from the JSON file,
      *         or an empty vector if the file doesn't exist or contains invalid JSON
      */
     std::vector<Book> readBooksFromFile(const std::string& filename);
     
     /**
      * @brief Writes a collection of Book objects to a JSON file
      * 
      * This function converts each Book object in the provided vector to a JSON representation
      * and writes the resulting JSON array to the specified file. The JSON is formatted
      * with indentation for improved readability.
      * 
      * @param filename Path to the JSON file to write
      * @param books Vector of Book objects to serialize to JSON
      * @return true if the write operation was successful,
      *         false if the file couldn't be written
      */
     bool writeBooksToFile(const std::string& filename, const std::vector<Book>& books);
     
     /**
      * @brief Converts a single Book object to a JSON string
      * 
      * This function serializes a Book object into a well-formatted JSON string
      * with all Book properties represented as JSON fields.
      * 
      * @param book The Book object to convert to JSON
      * @return A string containing the JSON representation of the Book
      */
     std::string bookToJson(const Book& book);
     
     /**
      * @brief Converts a JSON string to a Book object
      * 
      * This function deserializes a JSON string into a Book object,
      * mapping JSON fields to the corresponding Book properties.
      * 
      * @param jsonStr The JSON string to convert to a Book object
      * @return A Book object with properties set from the JSON data,
      *         or a default Book object if the JSON is invalid
      */
     Book jsonToBook(const std::string& jsonStr);
 }
 
 #endif // JSON_UTILS_HPP