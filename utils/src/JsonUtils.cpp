/**
 * @file JsonUtils.cpp
 * @brief Implementation of JSON serialization and deserialization utilities
 * @author Your Name
 * @date February 27, 2025
 * 
 * This file implements the utility functions declared in JsonUtils.hpp for
 * converting Book objects to and from JSON format, as well as file I/O operations
 * for JSON data. It uses the nlohmann/json library for JSON parsing and generation.
 */

// utils/src/JsonUtils.cpp
#include "JsonUtils.hpp"
#include "File.hpp"
#include <nlohmann/json.hpp>
#include <iostream>

// Create an alias for the nlohmann::json type to improve code readability
using json = nlohmann::json;

namespace JsonUtils {

/**
 * @brief Reads a collection of Book objects from a JSON file
 * 
 * This function performs the following steps:
 * 1. Checks if the specified file exists
 * 2. If not, creates an empty JSON array file
 * 3. Reads the file content
 * 4. Parses the JSON content
 * 5. Converts each JSON object in the array to a Book object
 * 
 * @param filename Path to the JSON file to read
 * @return Vector of Book objects parsed from the JSON file,
 *         or an empty vector if the file doesn't exist or contains invalid JSON
 * 
 * @note Error messages are output to stderr if JSON parsing fails
 */
std::vector<Book> readBooksFromFile(const std::string& filename) {
    std::vector<Book> books;
    
    // Check if the JSON file exists
    if (!FileUtils::fileExists(filename)) {
        // Create an empty JSON array file if it doesn't exist
        // This ensures we always have a valid starting point
        FileUtils::writeFile(filename, "[]");
        return books;  // Return empty vector
    }
    
    // Read the content of the JSON file
    std::string content = FileUtils::readFile(filename);
    if (content.empty()) {
        // If the file is empty or couldn't be read, return an empty vector
        return books;
    }
    
    try {
        // Parse the JSON content
        json j = json::parse(content);
        
        // Convert each JSON object to a Book object
        for (const auto& bookJson : j) {
            Book book;
            // Set each property of the Book object from the corresponding JSON field
            book.setId(bookJson["id"]);
            book.setTitle(bookJson["title"]);
            book.setAuthor(bookJson["author"]);
            book.setYear(bookJson["year"]);
            book.setAvailable(bookJson["available"]);
            // Add the Book to our result vector
            books.push_back(book);
        }
    } catch (const std::exception& e) {
        // Log any JSON parsing errors
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
    }
    
    return books;
}

/**
 * @brief Writes a collection of Book objects to a JSON file
 * 
 * This function performs the following steps:
 * 1. Creates an empty JSON array
 * 2. Converts each Book object to a JSON object
 * 3. Adds each JSON object to the array
 * 4. Writes the entire JSON array to the specified file with pretty formatting
 * 
 * @param filename Path to the JSON file to write
 * @param books Vector of Book objects to serialize to JSON
 * @return true if the write operation was successful,
 *         false if the file couldn't be written
 */
bool writeBooksToFile(const std::string& filename, const std::vector<Book>& books) {
    // Create an empty JSON array
    json j = json::array();
    
    // Convert each Book object to a JSON object and add it to the array
    for (const auto& book : books) {
        // Create a JSON object for the current book
        json bookJson;
        // Set JSON fields from Book properties
        bookJson["id"] = book.getId();
        bookJson["title"] = book.getTitle();
        bookJson["author"] = book.getAuthor();
        bookJson["year"] = book.getYear();
        bookJson["available"] = book.isAvailable();
        // Add the book JSON object to the array
        j.push_back(bookJson);
    }
    
    // Write the JSON array to the file with 4-space indentation for readability
    // The dump(4) method creates a pretty-printed JSON string
    return FileUtils::writeFile(filename, j.dump(4));
}

/**
 * @brief Converts a single Book object to a JSON string
 * 
 * This function creates a JSON object with fields corresponding to
 * each property of the provided Book object, then converts this JSON
 * object to a formatted string.
 * 
 * @param book The Book object to convert to JSON
 * @return A string containing the JSON representation of the Book
 */
std::string bookToJson(const Book& book) {
    // Create a JSON object
    json j;
    // Set JSON fields from Book properties
    j["id"] = book.getId();
    j["title"] = book.getTitle();
    j["author"] = book.getAuthor();
    j["year"] = book.getYear();
    j["available"] = book.isAvailable();
    
    // Convert the JSON object to a string with 4-space indentation
    return j.dump(4);
}

/**
 * @brief Converts a JSON string to a Book object
 * 
 * This function parses a JSON string and sets the properties of a
 * Book object based on the fields in the JSON data.
 * 
 * @param jsonStr The JSON string to convert to a Book object
 * @return A Book object with properties set from the JSON data,
 *         or a default Book object if the JSON is invalid
 * 
 * @note Error messages are output to stderr if JSON parsing fails
 */
Book jsonToBook(const std::string& jsonStr) {
    // Create a default Book object
    Book book;
    
    try {
        // Parse the JSON string
        json j = json::parse(jsonStr);
        
        // Set Book properties from JSON fields
        book.setId(j["id"]);
        book.setTitle(j["title"]);
        book.setAuthor(j["author"]);
        book.setYear(j["year"]);
        book.setAvailable(j["available"]);
    } catch (const std::exception& e) {
        // Log any JSON parsing errors
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
        // The default Book object will be returned in case of errors
    }
    
    return book;
}

} // namespace JsonUtils