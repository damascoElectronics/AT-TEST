// types/Book.cpp
/**
 * @file Book.cpp
 * @brief Implementation of the Book class methods
 * @author Your Name
 * @date February 27, 2025
 * 
 * This file contains the implementation of all methods declared in the Book class.
 * It provides the functionality for managing book properties and behaviors in the
 * library management system.
 */

 #include "models.hpp"

 /**
  * @brief Default constructor implementation
  * 
  * Initializes a Book object with default values:
  * - id: 0
  * - title: empty string
  * - author: empty string
  * - year: 0
  * - available: true (book is available by default)
  */
 Book::Book() : id(0), title(""), author(""), year(0), available(true) {}
 
 /**
  * @brief Parameterized constructor implementation
  * 
  * Creates a Book object with the specified properties and sets it as available.
  * 
  * @param id Unique identifier for the book
  * @param title Title of the book
  * @param author Author of the book
  * @param year Publication year of the book
  */
 Book::Book(int id, const std::string& title, const std::string& author, int year)
     : id(id), title(title), author(author), year(year), available(true) {}
 
 /**
  * @brief Implementation of getId() method
  * 
  * @return The unique ID of the book
  */
 int Book::getId() const {
     return id;
 }
 
 /**
  * @brief Implementation of getTitle() method
  * 
  * @return The title of the book
  */
 std::string Book::getTitle() const {
     return title;
 }
 
 /**
  * @brief Implementation of getAuthor() method
  * 
  * @return The author of the book
  */
 std::string Book::getAuthor() const {
     return author;
 }
 
 /**
  * @brief Implementation of getYear() method
  * 
  * @return The publication year of the book
  */
 int Book::getYear() const {
     return year;
 }
 
 /**
  * @brief Implementation of isAvailable() method
  * 
  * @return true if the book is available for borrowing, false otherwise
  */
 bool Book::isAvailable() const {
     return available;
 }
 
 /**
  * @brief Implementation of setId() method
  * 
  * Updates the book's ID to the specified value.
  * 
  * @param id The new ID to assign to the book
  */
 void Book::setId(int id) {
     this->id = id;  // 'this' pointer used to disambiguate parameter and member variable
 }
 
 /**
  * @brief Implementation of setTitle() method
  * 
  * Updates the book's title to the specified value.
  * 
  * @param title The new title to assign to the book
  */
 void Book::setTitle(const std::string& title) {
     this->title = title;  // 'this' pointer used to disambiguate parameter and member variable
 }
 
 /**
  * @brief Implementation of setAuthor() method
  * 
  * Updates the book's author to the specified value.
  * 
  * @param author The new author to assign to the book
  */
 void Book::setAuthor(const std::string& author) {
     this->author = author;  // 'this' pointer used to disambiguate parameter and member variable
 }
 
 /**
  * @brief Implementation of setYear() method
  * 
  * Updates the book's publication year to the specified value.
  * 
  * @param year The new publication year to assign to the book
  */
 void Book::setYear(int year) {
     this->year = year;  // 'this' pointer used to disambiguate parameter and member variable
 }
 
 /**
  * @brief Implementation of setAvailable() method
  * 
  * Updates the book's availability status to the specified value.
  * 
  * @param available The new availability status (true for available, false for unavailable)
  */
 void Book::setAvailable(bool available) {
     this->available = available;  // 'this' pointer used to disambiguate parameter and member variable
 }
 
 /**
  * @brief Implementation of borrow() method
  * 
  * Marks the book as unavailable (borrowed).
  * 
  * @note In a more robust implementation, this method should check if the book
  * is already borrowed and throw an exception if it is. Currently, it simply
  * sets the status to false regardless of the current status.
  */
 void Book::borrow() {
     available = false;
 }
 
 /**
  * @brief Implementation of returnBook() method
  * 
  * Marks the book as available (returned to the library).
  * 
  * @note In a more robust implementation, this method should check if the book
  * is already available and throw an exception if it is. Currently, it simply
  * sets the status to true regardless of the current status.
  */
 void Book::returnBook() {
     available = true;
 }