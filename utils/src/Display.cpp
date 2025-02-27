#include "Display.hpp"
#include <iostream>
#include <string>
#include <limits>  // For std::numeric_limits
#include <ctime>   // For time functions

namespace Display {

void displayMenu() {
    std::cout << "\nLibrary Management System\n";
    std::cout << "-------------------------\n";
    std::cout << "1. Add a new book\n";
    std::cout << "2. Search for a book\n";
    std::cout << "3. Borrow a book\n";
    std::cout << "4. Return a book\n";
    std::cout << "5. Display all books\n";
    std::cout << "6. Remove a book\n";
    std::cout << "0. Exit\n";
    std::cout << "Enter your choice: ";
}

void addBookMenu(Library& library) {
    std::string title, author;
    int year;
    bool validInput = false;
    
    std::cout << "\nAdd a new book\n";
    std::cout << "---------------\n";
    
    // Clear any leftover characters in the input buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    // Title validation loop
    do {
        std::cout << "Enter title (cannot be empty): ";
        std::getline(std::cin, title);
        
        if (title.empty()) {
            std::cout << "Error: Title cannot be empty. Please try again.\n";
        } else {
            validInput = true;
        }
    } while (!validInput);
    
    // Reset validation flag for author
    validInput = false;
    
    // Author validation loop
    do {
        std::cout << "Enter author (cannot be empty): ";
        std::getline(std::cin, author);
        
        if (author.empty()) {
            std::cout << "Error: Author cannot be empty. Please try again.\n";
        } else {
            validInput = true;
        }
    } while (!validInput);
    
    // Reset validation flag for year
    validInput = false;
    
    // Year validation loop
    do {
        std::cout << "Enter publication year (must be between 1000 and current year): ";
        
        // Check if input is a number
        if (!(std::cin >> year)) {
            std::cin.clear(); // Clear error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Error: Year must be a number. Please try again.\n";
            continue;
        }
        
        // Get current year for validation
        time_t now = time(0);
        tm *ltm = localtime(&now);
        int currentYear = 1900 + ltm->tm_year;
        
        // Validate year range (arbitrary minimum of 1000 to catch errors)
        if (year < 1000 || year > currentYear) {
            std::cout << "Error: Year must be between 1000 and " << currentYear << ". Please try again.\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            validInput = true;
        }
    } while (!validInput);
    
    // Now we can add the book since all inputs are valid
    if (library.addBook(title, author, year)) {
        std::cout << "Book added successfully.\n";
    } else {
        std::cout << "Failed to add book.\n";
    }
}

void searchBookMenu(Library& library) {
    int searchChoice;
    
    std::cout << "\nSearch for a book\n";
    std::cout << "-----------------\n";
    std::cout << "1. Search by ID\n";
    std::cout << "2. Search by title\n";
    std::cout << "3. Search by author\n";
    std::cout << "Enter your choice: ";
    std::cin >> searchChoice;
    
    switch (searchChoice) {
        case 1: {
            int id;
            std::cout << "Enter book ID: ";
            std::cin >> id;
            
            Book* book = library.findBookById(id);
            if (book) {
                std::cout << "\nBook found:\n";
                std::cout << "ID: " << book->getId() << "\n";
                std::cout << "Title: " << book->getTitle() << "\n";
                std::cout << "Author: " << book->getAuthor() << "\n";
                std::cout << "Year: " << book->getYear() << "\n";
                std::cout << "Available: " << (book->isAvailable() ? "Yes" : "No") << "\n";
            } else {
                std::cout << "Book not found.\n";
            }
            break;
        }
        case 2: {
            std::string title;
            std::cin.ignore();
            std::cout << "Enter book title: ";
            std::getline(std::cin, title);
            
            auto books = library.findBooksByTitle(title);
            if (!books.empty()) {
                std::cout << "\nBooks found:\n";
                for (const auto& book : books) {
                    std::cout << "ID: " << book.getId() << "\n";
                    std::cout << "Title: " << book.getTitle() << "\n";
                    std::cout << "Author: " << book.getAuthor() << "\n";
                    std::cout << "Year: " << book.getYear() << "\n";
                    std::cout << "Available: " << (book.isAvailable() ? "Yes" : "No") << "\n";
                    std::cout << "--------------------\n";
                }
            } else {
                std::cout << "No books found with that title.\n";
            }
            break;
        }
        case 3: {
            std::string author;
            std::cin.ignore();
            std::cout << "Enter author name: ";
            std::getline(std::cin, author);
            
            auto books = library.findBooksByAuthor(author);
            if (!books.empty()) {
                std::cout << "\nBooks found:\n";
                for (const auto& book : books) {
                    std::cout << "ID: " << book.getId() << "\n";
                    std::cout << "Title: " << book.getTitle() << "\n";
                    std::cout << "Author: " << book.getAuthor() << "\n";
                    std::cout << "Year: " << book.getYear() << "\n";
                    std::cout << "Available: " << (book.isAvailable() ? "Yes" : "No") << "\n";
                    std::cout << "--------------------\n";
                }
            } else {
                std::cout << "No books found by that author.\n";
            }
            break;
        }
        default:
            std::cout << "Invalid choice.\n";
    }
}

void borrowBookMenu(Library& library) {
    int id;
    
    std::cout << "\nBorrow a book\n";
    std::cout << "-------------\n";
    std::cout << "Enter book ID: ";
    std::cin >> id;
    
    if (library.borrowBook(id)) {
        std::cout << "Book borrowed successfully.\n";
    } else {
        std::cout << "Failed to borrow book. It may not exist or is already borrowed.\n";
    }
}

void returnBookMenu(Library& library) {
    int id;
    
    std::cout << "\nReturn a book\n";
    std::cout << "-------------\n";
    std::cout << "Enter book ID: ";
    std::cin >> id;
    
    if (library.returnBook(id)) {
        std::cout << "Book returned successfully.\n";
    } else {
        std::cout << "Failed to return book. It may not exist or is already available.\n";
    }
}

void removeBookMenu(Library& library) {
    int id;
    
    std::cout << "\nRemove a book\n";
    std::cout << "-------------\n";
    std::cout << "Enter book ID: ";
    std::cin >> id;
    
    if (library.removeBook(id)) {
        std::cout << "Book removed successfully.\n";
    } else {
        std::cout << "Failed to remove book. It may not exist.\n";
    }
}

} // namespace Display