// utils/src/JsonUtils.cpp
#include "JsonUtils.hpp"
#include "File.hpp"
#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

namespace JsonUtils {

std::vector<Book> readBooksFromFile(const std::string& filename) {
    std::vector<Book> books;
    
    if (!FileUtils::fileExists(filename)) {
        // Create an empty JSON array file if it doesn't exist
        FileUtils::writeFile(filename, "[]");
        return books;
    }
    
    std::string content = FileUtils::readFile(filename);
    if (content.empty()) {
        return books;
    }
    
    try {
        json j = json::parse(content);
        
        for (const auto& bookJson : j) {
            Book book;
            book.setId(bookJson["id"]);
            book.setTitle(bookJson["title"]);
            book.setAuthor(bookJson["author"]);
            book.setYear(bookJson["year"]);
            book.setAvailable(bookJson["available"]);
            books.push_back(book);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
    }
    
    return books;
}

bool writeBooksToFile(const std::string& filename, const std::vector<Book>& books) {
    json j = json::array();
    
    for (const auto& book : books) {
        json bookJson;
        bookJson["id"] = book.getId();
        bookJson["title"] = book.getTitle();
        bookJson["author"] = book.getAuthor();
        bookJson["year"] = book.getYear();
        bookJson["available"] = book.isAvailable();
        j.push_back(bookJson);
    }
    
    return FileUtils::writeFile(filename, j.dump(4)); // Pretty print with 4-space indentation
}

std::string bookToJson(const Book& book) {
    json j;
    j["id"] = book.getId();
    j["title"] = book.getTitle();
    j["author"] = book.getAuthor();
    j["year"] = book.getYear();
    j["available"] = book.isAvailable();
    
    return j.dump(4);
}

Book jsonToBook(const std::string& jsonStr) {
    Book book;
    try {
        json j = json::parse(jsonStr);
        book.setId(j["id"]);
        book.setTitle(j["title"]);
        book.setAuthor(j["author"]);
        book.setYear(j["year"]);
        book.setAvailable(j["available"]);
    } catch (const std::exception& e) {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
    }
    
    return book;
}

} // namespace JsonUtils