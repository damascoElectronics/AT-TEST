// types/Book.hpp
/**
 * @file Book.hpp
 * @brief Header file defining the Book class and its properties/methods
 * @author Your Name
 * @date February 27, 2025
 * 
 * This file contains the Book class definition which represents a book entity
 * in the library management system. The class encapsulates all characteristics
 * and behaviors associated with physical book resources.
 */


#ifndef BOOK_HPP
#define BOOK_HPP

/**
 * @class Book
 * @brief Represents a book entity with its properties and behaviors
 * 
 * The Book class models physical books in a library system, tracking
 * properties such as ID, title, author, publication year, and availability status.
 * It also provides methods for borrowing and returning books.
 */

#include <string>

class Book {
private:
    int id;                 /// @brief Unique identifier for the book
    std::string title;      /// @brief Title of the book
    std::string author;     /// @brief Author of the book
    int year;               /// @brief Publication year of the book
    bool available;          /// @brief Flag indicating whether the book is currently available for borrowing

public:
    /**
     * @brief Default constructor
     * 
     * Creates an empty Book object with default values
     */
    Book();

    /**
     * @brief Parameterized constructor
     * 
     * @param id Unique identifier for the book
     * @param title Title of the book
     * @param author Author of the book
     * @param year Publication year of the book
     * 
     * @note The book is set as available by default when created
     */
    Book(int id, 
        const std::string& title, 
        const std::string& author, 
        int year);
    
    // Getters
    /**
     * @brief Get the book's unique identifier
     * @return The unique ID of the book
     */
    int getId() const;
 
    /**
     * @brief Get the book's title
     * @return The title of the book
     */
    std::string getTitle() const;
     
    /**
     * @brief Get the book's author
     * @return The author of the book
     */
    std::string getAuthor() const;

    /**
     * @brief Get the book's publication year
     * @return The year the book was published
     */
    int getYear() const;

    /**
     * @brief Get the book's publication year
     * @return The year the book was published
     */
    bool isAvailable() const;
    
    // Setters

    /**
     * @brief Set the book's unique identifier
     * @param id The new ID to assign to the book
     */
    void setId(int id);

    /**
     * @brief Set the book's title
     * @param title The new title to assign to the book
     */
    void setTitle(const std::string& title);

    /**
     * @brief Set the book's author
     * @param author The new author to assign to the book
     */
    void setAuthor(const std::string& author);

    /**
     * @brief Set the book's publication year
     * @param year The new publication year to assign to the book
     */
    void setYear(int year);

    /**
     * @brief Set the book's availability status
     * @param available The new availability status (true for available, false for unavailable)
     */
    void setAvailable(bool available);
    
    // Other methods

    /**
     * @brief Process a book borrowing transaction
     * 
     * Sets the book's availability status to false, indicating it has been borrowed.
     * @throws std::runtime_error if the book is already borrowed
     */
    void borrow();
    
    /**
     * @brief Process a book return transaction
     * 
     * Sets the book's availability status to true, indicating it has been returned.
     * @throws std::runtime_error if the book is already available
     */
    void returnBook();
};

#endif // BOOK_HPP