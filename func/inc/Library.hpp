// func/inc/Library.hpp
#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <string>
#include <vector>
#include "models.hpp"

class Library {
private:
    std::vector<Book> books;
    std::string dataFile;
    int nextId;
    
    // Helper methods
    void loadBooks();
    void saveBooks();
    
public:
    // Constructor
    Library(const std::string& dataFile = "data/books.json");
    
    // Book management methods
    bool addBook(const std::string& title, const std::string& author, int year);
    bool removeBook(int id);
    Book* findBookById(int id);
    std::vector<Book> findBooksByTitle(const std::string& title);
    std::vector<Book> findBooksByAuthor(const std::string& author);
    
    // Book operations
    bool borrowBook(int id);
    bool returnBook(int id);
    
    // Display methods
    std::vector<Book> getAllBooks() const;
    void displayAllBooks() const;
};

#endif // LIBRARY_HPP