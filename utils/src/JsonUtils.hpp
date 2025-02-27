// utils/src/JsonUtils.cpp
#include "JsonUtils.hpp"
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace JsonUtils {

std::vector<Book> readBooksFromFile(const std::string& filename) {
    std::vector<Book> books;
    std::ifstream file(filename);
    
    if (file.is_open()) {
        try {
            json j;
            file >> j;
            
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
            // Handle JSON parsing errors
        }
        file.close();
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
    
    std::ofstream file(filename);
    if (file.is_open()) {
        file << j.dump(4); // Pretty print with 4-space indentation
        file.close();
        return true;
    }
    
    return false;
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
        // Handle JSON parsing errors
    }
    
    return book;
}

} // namespace JsonUtils