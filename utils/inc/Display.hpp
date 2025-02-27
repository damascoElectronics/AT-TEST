/**
 * @file Display.hpp
 * @brief Header file declaring user interface functions for the library management system
 * @author Your Name
 * @date February 27, 2025
 * 
 * This file contains declarations for functions that handle the user interface
 * aspects of the library management system. The Display namespace provides
 * menu-driven interfaces for interacting with a Library object, including
 * displaying menus, collecting user input, validating that input, and calling
 * the appropriate Library methods to perform the requested operations.
 */

 #ifndef DISPLAY_HPP
 #define DISPLAY_HPP
 
 #include "Library.hpp"
 
 /**
  * @namespace Display
  * @brief Namespace containing user interface functions for the library management system
  * 
  * This namespace encapsulates functions that provide the text-based user interface
  * for the library management system. It separates the presentation layer from the
  * business logic layer (contained in the Library class), following the separation
  * of concerns design principle. Each function in this namespace handles a specific
  * user interaction scenario, such as displaying a menu, collecting and validating
  * user input, and calling the appropriate Library methods.
  */
 namespace Display {
     /**
      * @brief Displays the main menu options for the library management system
      * 
      * This function prints the main menu options to the standard output, showing
      * the user what operations they can perform. It does not collect or process
      * user input; that responsibility belongs to the main program loop.
      */
     void displayMenu();
     
     /**
      * @brief Displays the add book interface and processes user input
      * 
      * This function guides the user through the process of adding a new book to
      * the library. It collects and validates input for the book's title, author,
      * and publication year, then calls the Library's addBook method to add the book.
      * 
      * @param library Reference to the Library object to add the book to
      */
     void addBookMenu(Library& library);
     
     /**
      * @brief Displays the search book interface and processes user input
      * 
      * This function provides a submenu for searching books in various ways
      * (by ID, title, or author). It collects user input for the search method
      * and search terms, then calls the appropriate Library search method and
      * displays the results.
      * 
      * @param library Reference to the Library object to search in
      */
     void searchBookMenu(Library& library);
     
     /**
      * @brief Displays the borrow book interface and processes user input
      * 
      * This function guides the user through the process of borrowing a book.
      * It collects input for the book ID, then calls the Library's borrowBook
      * method and displays the result of the operation.
      * 
      * @param library Reference to the Library object to borrow from
      */
     void borrowBookMenu(Library& library);
     
     /**
      * @brief Displays the return book interface and processes user input
      * 
      * This function guides the user through the process of returning a book.
      * It collects input for the book ID, then calls the Library's returnBook
      * method and displays the result of the operation.
      * 
      * @param library Reference to the Library object to return to
      */
     void returnBookMenu(Library& library);
     
     /**
      * @brief Displays the remove book interface and processes user input
      * 
      * This function guides the user through the process of removing a book
      * from the library. It collects input for the book ID, then calls the
      * Library's removeBook method and displays the result of the operation.
      * 
      * @param library Reference to the Library object to remove from
      */
     void removeBookMenu(Library& library);
 }
 
 #endif // DISPLAY_HPP