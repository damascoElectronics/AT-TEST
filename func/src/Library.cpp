/**
 * @file Library.cpp
 * @brief Implementation of the Library class for the library management system
 * @author Your Name
 * @date February 27, 2025
 * 
 * This file implements the Library class methods declared in Library.hpp.
 * It contains the core functionality of the library management system,
 * handling book operations such as adding, removing, finding, borrowing,
 * and returning books, as well as data persistence using the JsonUtils module.
 */

// func/src/Library.cpp
#include "Library.hpp"
#include "JsonUtils.hpp"
#include <iostream>
#include <algorithm>

/**
 * @brief Constructor implementation for the Library class
 * 
 * Initializes a Library object with the specified data file path
 * and loads existing books from that file. Sets the nextId counter
 * based on the highest book ID found in the loaded collection.
 * 
 * @param dataFile Path to the JSON file where book data is stored
 */
Library::Library(const std::string& dataFile) : dataFile(dataFile), nextId(1) {
    loadBooks();
}

/**
 * @brief Implementation of the loadBooks method
 * 
 * Reads books from the JSON data file using JsonUtils and populates
 * the books collection. After loading, it computes the next available
 * book ID by finding the highest ID in the collection and adding 1.
 * If no books are loaded (empty library), nextId remains at its
 * initial value of 1.
 */
void Library::loadBooks() {
    // Load books from the JSON file
    books = JsonUtils::readBooksFromFile(dataFile);
    
    // Find the highest ID to set nextId correctly
    if (!books.empty()) {
        // Use std::max_element with a lambda function to find the book with the highest ID
        auto maxIdBook = std::max_element(books.begin(), books.end(),
            [](const Book& a, const Book& b) { return a.getId() < b.getId(); });
        
        // Set nextId to one more than the highest ID found
        nextId = maxIdBook->getId() + 1;
    }
}

/**
 * @brief Implementation of the saveBooks method
 * 
 * Writes the current books collection to the JSON data file
 * using JsonUtils. This method is called after any operation
 * that modifies the books collection to ensure data persistence.
 */
void Library::saveBooks() {
    JsonUtils::writeBooksToFile(dataFile, books);
}

/**
 * @brief Implementation of the addBook method
 * 
 * Creates a new Book object with the provided details and the next
 * available ID, adds it to the library's collection, and saves the
 * updated collection to the data file.
 * 
 * @param title Title of the book
 * @param author Author of the book
 * @param year Publication year of the book
 * @return true (operation always succeeds in current implementation)
 * 
 * @note In a more robust implementation, this method might perform
 *       validation on the input parameters and return false if validation
 *       fails or if there's an error saving the data.
 */
bool Library::addBook(const std::string& title, const std::string& author, int year) {
    // Create a new book with the next available ID
    Book newBook(nextId++, title, author, year);
    
    // Add the book to our collection
    books.push_back(newBook);
    
    // Save the updated collection to the data file
    saveBooks();
    
    return true;
}

/**
 * @brief Implementation of the removeBook method
 * 
 * Searches for a book with the specified ID in the library's collection.
 * If found, removes it from the collection and saves the updated collection
 * to the data file.
 * 
 * @param id Unique identifier of the book to remove
 * @return true if the book was found and removed, false otherwise
 */
bool Library::removeBook(int id) {
    // Find the book with the specified ID using a lambda function
    auto it = std::find_if(books.begin(), books.end(),
        [id](const Book& book) { return book.getId() == id; });
    
    // If the book was found, remove it and save changes
    if (it != books.end()) {
        books.erase(it);
        saveBooks();
        return true;
    }
    
    // Book not found
    return false;
}

/**
 * @brief Implementation of the findBookById method
 * 
 * Searches for a book with the specified ID in the library's collection
 * and returns a pointer to it if found.
 * 
 * @param id Unique identifier of the book to find
 * @return Pointer to the Book object if found, nullptr otherwise
 * 
 * @note The returned pointer points to an object within the books vector,
 *       so it becomes invalid if the vector is modified (e.g., by adding
 *       or removing books).
 */
Book* Library::findBookById(int id) {
    // Find the book with the specified ID using a lambda function
    auto it = std::find_if(books.begin(), books.end(),
        [id](const Book& book) { return book.getId() == id; });
    
    // If the book was found, return a pointer to it
    if (it != books.end()) {
        return &(*it);
    }
    
    // Book not found
    return nullptr;
}

/**
 * @brief Implementation of the findBooksByTitle method
 * 
 * Searches for books whose titles contain the specified string
 * (case-sensitive partial match) and returns a vector of matching books.
 * 
 * @param title String to search for in book titles
 * @return Vector of Book objects with matching titles
 */
std::vector<Book> Library::findBooksByTitle(const std::string& title) {
    std::vector<Book> result;
    
    // Use std::copy_if with a lambda function to find books with matching titles
    std::copy_if(books.begin(), books.end(), std::back_inserter(result),
        [&title](const Book& book) {
            // Check if the book's title contains the search string
            return book.getTitle().find(title) != std::string::npos;
        });
    
    return result;
}

/**
 * @brief Implementation of the findBooksByAuthor method
 * 
 * Searches for books whose authors contain the specified string
 * (case-sensitive partial match) and returns a vector of matching books.
 * 
 * @param author String to search for in book authors
 * @return Vector of Book objects with matching authors
 */
std::vector<Book> Library::findBooksByAuthor(const std::string& author) {
    std::vector<Book> result;
    
    // Use std::copy_if with a lambda function to find books with matching authors
    std::copy_if(books.begin(), books.end(), std::back_inserter(result),
        [&author](const Book& book) {
            // Check if the book's author contains the search string
            return book.getAuthor().find(author) != std::string::npos;
        });
    
    return result;
}

/**
 * @brief Implementation of the borrowBook method
 * 
 * Finds the book with the specified ID and marks it as borrowed
 * (unavailable) if it is currently available.
 * 
 * @param id Unique identifier of the book to borrow
 * @return true if the book was found and successfully borrowed,
 *         false if the book was not found or is already borrowed
 */
bool Library::borrowBook(int id) {
    // Find the book with the specified ID
    Book* book = findBookById(id);
    
    // If the book was found and is available, mark it as borrowed
    if (book && book->isAvailable()) {
        book->borrow();
        saveBooks();
        return true;
    }
    
    // Book not found or not available
    return false;
}

/**
 * @brief Implementation of the returnBook method
 * 
 * Finds the book with the specified ID and marks it as returned
 * (available) if it is currently borrowed.
 * 
 * @param id Unique identifier of the book to return
 * @return true if the book was found and successfully returned,
 *         false if the book was not found or is already available
 */
bool Library::returnBook(int id) {
    // Find the book with the specified ID
    Book* book = findBookById(id);
    
    // If the book was found and is borrowed, mark it as returned
    if (book && !book->isAvailable()) {
        book->returnBook();
        saveBooks();
        return true;
    }
    
    // Book not found or already available
    return false;
}

/**
 * @brief Implementation of the getAllBooks method
 * 
 * @return Vector containing all Book objects in the library
 */
std::vector<Book> Library::getAllBooks() const {
    return books;
}

/**
 * @brief Implementation of the displayAllBooks method
 * 
 * Prints a formatted table of all books in the library to the standard
 * output, showing each book's ID, title, author, year, and availability.
 * If the library is empty, displays a message indicating that.
 */
void Library::displayAllBooks() const {
    // Check if the library is empty
    if (books.empty()) {
        std::cout << "No books in the library." << std::endl;
        return;
    }
    
    // Display header for the book table
    std::cout << "Library Books:" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "ID | Title | Author | Year | Available" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    
    // Display each book's details in a formatted row
    for (const auto& book : books) {
        std::cout << book.getId() << " | "
                  << book.getTitle() << " | "
                  << book.getAuthor() << " | "
                  << book.getYear() << " | "
                  << (book.isAvailable() ? "Yes" : "No") << std::endl;
    }
    
    // Display footer for the book table
    std::cout << "----------------------------------------" << std::endl;
}