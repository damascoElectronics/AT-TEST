/**
 * @file Display.cpp
 * @brief Implementation of user interface functions for the library management system
 * @author Your Name
 * @date February 27, 2025
 * 
 * This file implements the user interface functions declared in Display.hpp.
 * It contains the code for displaying menus, collecting and validating user input,
 * and interacting with the Library class to perform operations requested by the user.
 * The implementation focuses on providing a robust and user-friendly text-based
 * interface with appropriate input validation and error handling.
 */

 #include "Display.hpp"
 #include <iostream>
 #include <string>
 #include <limits>  // For std::numeric_limits
 #include <ctime>   // For time functions
 
 namespace Display {
 
 /**
  * @brief Implementation of the displayMenu function
  * 
  * Prints the main menu options to the standard output, showing the user
  * what operations they can perform in the library management system.
  */
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
 
 /**
  * @brief Implementation of the addBookMenu function
  * 
  * This function guides the user through the process of adding a new book
  * to the library. It performs the following steps:
  * 1. Collects and validates the book title (must not be empty)
  * 2. Collects and validates the author name (must not be empty)
  * 3. Collects and validates the publication year (must be a number between 1000 and current year)
  * 4. Calls the Library's addBook method to add the book
  * 5. Displays a success or failure message
  * 
  * Input validation is performed in loops that continue until valid input is provided.
  * 
  * @param library Reference to the Library object to add the book to
  */
 void addBookMenu(Library& library) {
     std::string title, author;
     int year;
     bool validInput = false;
     
     std::cout << "\nAdd a new book\n";
     std::cout << "---------------\n";
     
     // Clear any leftover characters in the input buffer
     // This is important when transitioning from numeric to string input
     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
     
     // Title validation loop
     do {
         std::cout << "Enter title (cannot be empty): ";
         std::getline(std::cin, title);
         
         // Validate that the title is not empty
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
         
         // Validate that the author is not empty
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
             // Clear error flag from failed input operation
             std::cin.clear();
             // Discard invalid input
             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
 
 /**
  * @brief Implementation of the searchBookMenu function
  * 
  * This function provides a submenu for searching books in various ways. It:
  * 1. Displays search options (by ID, title, or author)
  * 2. Collects user choice and search terms
  * 3. Calls the appropriate Library search method
  * 4. Displays the search results
  * 
  * @param library Reference to the Library object to search in
  */
 void searchBookMenu(Library& library) {
     int searchChoice;
     
     std::cout << "\nSearch for a book\n";
     std::cout << "-----------------\n";
     std::cout << "1. Search by ID\n";
     std::cout << "2. Search by title\n";
     std::cout << "3. Search by author\n";
     std::cout << "Enter your choice: ";
     std::cin >> searchChoice;
     
     // Process the user's search choice
     switch (searchChoice) {
         case 1: {
             // Search by ID
             int id;
             std::cout << "Enter book ID: ";
             std::cin >> id;
             
             // Find and display the book
             Book* book = library.findBookById(id);
             if (book) {
                 // Book found, display its details
                 std::cout << "\nBook found:\n";
                 std::cout << "ID: " << book->getId() << "\n";
                 std::cout << "Title: " << book->getTitle() << "\n";
                 std::cout << "Author: " << book->getAuthor() << "\n";
                 std::cout << "Year: " << book->getYear() << "\n";
                 std::cout << "Available: " << (book->isAvailable() ? "Yes" : "No") << "\n";
             } else {
                 // Book not found
                 std::cout << "Book not found.\n";
             }
             break;
         }
         case 2: {
             // Search by title
             std::string title;
             // Clear input buffer before reading string
             std::cin.ignore();
             std::cout << "Enter book title: ";
             std::getline(std::cin, title);
             
             // Find and display books with matching titles
             auto books = library.findBooksByTitle(title);
             if (!books.empty()) {
                 // Books found, display their details
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
                 // No books found
                 std::cout << "No books found with that title.\n";
             }
             break;
         }
         case 3: {
             // Search by author
             std::string author;
             // Clear input buffer before reading string
             std::cin.ignore();
             std::cout << "Enter author name: ";
             std::getline(std::cin, author);
             
             // Find and display books by the specified author
             auto books = library.findBooksByAuthor(author);
             if (!books.empty()) {
                 // Books found, display their details
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
                 // No books found
                 std::cout << "No books found by that author.\n";
             }
             break;
         }
         default:
             // Invalid search choice
             std::cout << "Invalid choice.\n";
     }
 }
 
 /**
  * @brief Implementation of the borrowBookMenu function
  * 
  * This function guides the user through the process of borrowing a book.
  * It collects the book ID, calls the Library's borrowBook method, and
  * displays the result of the operation.
  * 
  * @param library Reference to the Library object to borrow from
  */
 void borrowBookMenu(Library& library) {
     int id;
     
     std::cout << "\nBorrow a book\n";
     std::cout << "-------------\n";
     std::cout << "Enter book ID: ";
     std::cin >> id;
     
     // Attempt to borrow the book
     if (library.borrowBook(id)) {
         // Success
         std::cout << "Book borrowed successfully.\n";
     } else {
         // Failure (could be because book doesn't exist or is already borrowed)
         std::cout << "Failed to borrow book. It may not exist or is already borrowed.\n";
     }
 }
 
 /**
  * @brief Implementation of the returnBookMenu function
  * 
  * This function guides the user through the process of returning a book.
  * It collects the book ID, calls the Library's returnBook method, and
  * displays the result of the operation.
  * 
  * @param library Reference to the Library object to return to
  */
 void returnBookMenu(Library& library) {
     int id;
     
     std::cout << "\nReturn a book\n";
     std::cout << "-------------\n";
     std::cout << "Enter book ID: ";
     std::cin >> id;
     
     // Attempt to return the book
     if (library.returnBook(id)) {
         // Success
         std::cout << "Book returned successfully.\n";
     } else {
         // Failure (could be because book doesn't exist or is already available)
         std::cout << "Failed to return book. It may not exist or is already available.\n";
     }
 }
 
 /**
  * @brief Implementation of the removeBookMenu function
  * 
  * This function guides the user through the process of removing a book
  * from the library. It collects the book ID, calls the Library's removeBook
  * method, and displays the result of the operation.
  * 
  * @param library Reference to the Library object to remove from
  */
 void removeBookMenu(Library& library) {
     int id;
     
     std::cout << "\nRemove a book\n";
     std::cout << "-------------\n";
     std::cout << "Enter book ID: ";
     std::cin >> id;
     
     // Attempt to remove the book
     if (library.removeBook(id)) {
         // Success
         std::cout << "Book removed successfully.\n";
     } else {
         // Failure (could be because book doesn't exist)
         std::cout << "Failed to remove book. It may not exist.\n";
     }
 }
 
 } // namespace Display