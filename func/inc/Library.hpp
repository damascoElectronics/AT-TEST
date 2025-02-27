/**
 * @file Library.hpp
 * @brief Header file defining the Library class for managing book collections
 * @author Your Name
 * @date February 27, 2025
 * 
 * This file contains the definition of the Library class, which serves as the main
 * facade for the library management system. It provides high-level operations for
 * managing a collection of books, such as adding, finding, borrowing, and returning
 * books. The Library class abstracts away the details of data persistence and
 * book management, providing a clean and simple interface for client code.
 */

// func/inc/Library.hpp
#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <string>
#include <vector>
#include "models.hpp"

/**
 * @class Library
 * @brief Main class for managing a collection of books in the library system
 * 
 * The Library class provides a comprehensive set of operations for managing
 * a library's book collection. It handles the loading and saving of book data
 * from/to persistent storage (JSON files), and provides methods for adding,
 * removing, finding, borrowing, and returning books. It also maintains the
 * state of the library, including the next available book ID.
 */
class Library {
private:
    /// @brief Collection of books in the library
    std::vector<Book> books;
    
    /// @brief Path to the JSON file where book data is stored
    std::string dataFile;
    
    /// @brief Next available ID for new books
    int nextId;
    
    /**
     * @brief Loads books from the data file into memory
     * 
     * This method is called during Library initialization to populate
     * the books collection from the JSON data file. It also sets the
     * nextId value based on the highest existing book ID.
     */
    void loadBooks();
    
    /**
     * @brief Saves the current books collection to the data file
     * 
     * This method is called after any operation that modifies the
     * books collection to ensure the changes are persisted to disk.
     */
    void saveBooks();
    
public:
    /**
     * @brief Constructor for the Library class
     * 
     * Initializes a Library object and loads existing books from the
     * specified data file. If the file doesn't exist, an empty library
     * is created and the file will be created when the first book is added.
     * 
     * @param dataFile Path to the JSON file where book data is stored
     *                 (defaults to "data/books.json")
     */
    Library(const std::string& dataFile = "data/books.json");
    
    /**
     * @brief Adds a new book to the library
     * 
     * Creates a new Book object with the provided details and a unique ID,
     * adds it to the library's collection, and persists the changes to disk.
     * 
     * @param title Title of the book
     * @param author Author of the book
     * @param year Publication year of the book
     * @return true if the book was successfully added, false otherwise
     */
    bool addBook(const std::string& title, const std::string& author, int year);
    
    /**
     * @brief Removes a book from the library
     * 
     * Searches for a book with the specified ID and removes it from the
     * library's collection if found, then persists the changes to disk.
     * 
     * @param id Unique identifier of the book to remove
     * @return true if the book was found and removed, false otherwise
     */
    bool removeBook(int id);
    
    /**
     * @brief Finds a book by its ID
     * 
     * Searches for a book with the specified ID and returns a pointer to it.
     * 
     * @param id Unique identifier of the book to find
     * @return Pointer to the Book object if found, nullptr otherwise
     * 
     * @note The returned pointer points to an object within the Library's
     *       internal collection, so it becomes invalid if the collection
     *       is modified (e.g., by adding or removing books).
     */
    Book* findBookById(int id);
    
    /**
     * @brief Finds books by title (partial match)
     * 
     * Searches for books whose titles contain the specified string
     * (case-sensitive) and returns a vector of matching books.
     * 
     * @param title String to search for in book titles
     * @return Vector of Book objects with matching titles
     */
    std::vector<Book> findBooksByTitle(const std::string& title);
    
    /**
     * @brief Finds books by author (partial match)
     * 
     * Searches for books whose authors contain the specified string
     * (case-sensitive) and returns a vector of matching books.
     * 
     * @param author String to search for in book authors
     * @return Vector of Book objects with matching authors
     */
    std::vector<Book> findBooksByAuthor(const std::string& author);
    
    /**
     * @brief Marks a book as borrowed
     * 
     * Finds the book with the specified ID and marks it as borrowed
     * (unavailable) if it is currently available.
     * 
     * @param id Unique identifier of the book to borrow
     * @return true if the book was found and successfully borrowed,
     *         false if the book was not found or is already borrowed
     */
    bool borrowBook(int id);
    
    /**
     * @brief Marks a book as returned
     * 
     * Finds the book with the specified ID and marks it as returned
     * (available) if it is currently borrowed.
     * 
     * @param id Unique identifier of the book to return
     * @return true if the book was found and successfully returned,
     *         false if the book was not found or is already available
     */
    bool returnBook(int id);
    
    /**
     * @brief Gets all books in the library
     * 
     * @return Vector containing all Book objects in the library
     */
    std::vector<Book> getAllBooks() const;
    
    /**
     * @brief Displays all books in the library to the console
     * 
     * Prints a formatted table of all books in the library to the standard
     * output, showing each book's ID, title, author, year, and availability.
     */
    void displayAllBooks() const;
};

#endif // LIBRARY_HPP