/**
 * @file main.cpp
 * @brief Main entry point for the library management system
 * @author Your Name
 * @date February 27, 2025
 * 
 * This file contains the main() function that serves as the entry point for
 * the library management system application. It initializes the Library object,
 * displays the main menu, processes user choices, and delegates to appropriate
 * functions in the Display namespace. The program runs in a loop until the user
 * chooses to exit.
 * 
 * This file represents the integration layer of the application, tying together
 * the business logic (Library class) and the user interface (Display namespace).
 */

 #include <iostream>
 #include <string>
 #include "Library.hpp"
 #include "Display.hpp"
 
 /**
  * @brief Main entry point for the library management system
  * 
  * This function performs the following steps:
  * 1. Initializes a Library object with the default data file path
  * 2. Enters a menu loop that displays options and processes user input
  * 3. Delegates to appropriate Display functions based on user choices
  * 4. Continues the loop until the user chooses to exit (option 0)
  * 
  * The main function serves as the controller in the application's architecture,
  * coordinating between the user interface (Display namespace) and the business
  * logic (Library class).
  * 
  * @return 0 on successful execution
  */
 int main() {
     // Initialize the Library object with the path to the JSON data file
     // This will load any existing books from the file
     Library library("data/books.json");
     
     // Variable to store the user's menu choice
     int choice;
     
     // Main program loop - continues until user chooses to exit
     do {
         // Display the main menu and prompt for user input
         Display::displayMenu();
         std::cin >> choice;
         
         // Process the user's choice
         switch (choice) {
             case 1:
                 // Add a new book
                 Display::addBookMenu(library);
                 break;
             case 2:
                 // Search for a book
                 Display::searchBookMenu(library);
                 break;
             case 3:
                 // Borrow a book
                 Display::borrowBookMenu(library);
                 break;
             case 4:
                 // Return a book
                 Display::returnBookMenu(library);
                 break;
             case 5:
                 // Display all books in the library
                 library.displayAllBooks();
                 break;
             case 6:
                 // Remove a book from the library
                 Display::removeBookMenu(library);
                 break;
             case 0:
                 // Exit the program
                 std::cout << "Exiting. Goodbye!\n";
                 break;
             default:
                 // Handle invalid menu choices
                 std::cout << "Invalid choice. Please try again.\n";
         }
     } while (choice != 0);  // Continue until the exit option is selected
     
     // Return 0 to indicate successful program execution
     return 0;
 }