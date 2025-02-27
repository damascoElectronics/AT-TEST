// func/src/Library.cpp
#include "Library.hpp"
#include "JsonUtils.hpp"
#include <iostream>
#include <algorithm>

Library::Library(const std::string& dataFile) : dataFile(dataFile), nextId(1) {
    loadBooks();
}

void Library::loadBooks() {
    books = JsonUtils::readBooksFromFile(dataFile);
    
    // Find the highest ID to set nextId correctly
    if (!books.empty()) {
        auto maxIdBook = std::max_element(books.begin(), books.end(),
            [](const Book& a, const Book& b) { return a.getId() < b.getId(); });
        nextId = maxIdBook->getId() + 1;
    }
}

void Library::saveBooks() {
    JsonUtils::writeBooksToFile(dataFile, books);
}

bool Library::addBook(const std::string& title, const std::string& author, int year) {
    Book newBook(nextId++, title, author, year);
    books.push_back(newBook);
    saveBooks();
    return true;
}

bool Library::removeBook(int id) {
    auto it = std::find_if(books.begin(), books.end(),
        [id](const Book& book) { return book.getId() == id; });
    
    if (it != books.end()) {
        books.erase(it);
        saveBooks();
        return true;
    }
    
    return false;
}

Book* Library::findBookById(int id) {
    auto it = std::find_if(books.begin(), books.end(),
        [id](const Book& book) { return book.getId() == id; });
    
    if (it != books.end()) {
        return &(*it);
    }
    
    return nullptr;
}

std::vector<Book> Library::findBooksByTitle(const std::string& title) {
    std::vector<Book> result;
    std::copy_if(books.begin(), books.end(), std::back_inserter(result),
        [&title](const Book& book) {
            return book.getTitle().find(title) != std::string::npos;
        });
    
    return result;
}

std::vector<Book> Library::findBooksByAuthor(const std::string& author) {
    std::vector<Book> result;
    std::copy_if(books.begin(), books.end(), std::back_inserter(result),
        [&author](const Book& book) {
            return book.getAuthor().find(author) != std::string::npos;
        });
    
    return result;
}

bool Library::borrowBook(int id) {
    Book* book = findBookById(id);
    
    if (book && book->isAvailable()) {
        book->borrow();
        saveBooks();
        return true;
    }
    
    return false;
}

bool Library::returnBook(int id) {
    Book* book = findBookById(id);
    
    if (book && !book->isAvailable()) {
        book->returnBook();
        saveBooks();
        return true;
    }
    
    return false;
}

std::vector<Book> Library::getAllBooks() const {
    return books;
}

void Library::displayAllBooks() const {
    if (books.empty()) {
        std::cout << "No books in the library." << std::endl;
        return;
    }
    
    std::cout << "Library Books:" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "ID | Title | Author | Year | Available" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    
    for (const auto& book : books) {
        std::cout << book.getId() << " | "
                  << book.getTitle() << " | "
                  << book.getAuthor() << " | "
                  << book.getYear() << " | "
                  << (book.isAvailable() ? "Yes" : "No") << std::endl;
    }
    
    std::cout << "----------------------------------------" << std::endl;
}