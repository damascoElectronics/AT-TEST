

#ifndef JSON_UTILS_HPP
#define JSON_UTILS_HPP

#include <string>
#include <vector>
#include "models.hpp"

namespace JsonUtils {
    // Read books from JSON file
    std::vector<Book> readBooksFromFile(const std::string& filename);
    
    // Write books to JSON file
    bool writeBooksToFile(const std::string& filename, const std::vector<Book>& books);
    
    // Convert Book to JSON string
    std::string bookToJson(const Book& book);
    
    // Convert JSON string to Book
    Book jsonToBook(const std::string& jsonStr);
}

#endif // JSON_UTILS_HPP