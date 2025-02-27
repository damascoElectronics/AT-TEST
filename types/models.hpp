// types/Book.hpp
/**
 * this header file is for defining the charateristics of the books
 */

#ifndef BOOK_HPP
#define BOOK_HPP

#include <string>

class Book {
private:
    int id;
    std::string title;
    std::string author;
    int year;
    bool available;

public:
    // Constructors
    Book();
    Book(int id, 
        const std::string& title, 
        const std::string& author, 
        int year);
    
    // Getters
    int getId() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    int getYear() const;
    bool isAvailable() const;
    
    // Setters
    void setId(int id);
    void setTitle(const std::string& title);
    void setAuthor(const std::string& author);
    void setYear(int year);
    void setAvailable(bool available);
    
    // Other methods
    void borrow();
    void returnBook();
};

#endif // BOOK_HPP