#include <iostream>
#include <string>
#include "Library.hpp"
#include "Display.hpp"

int main() {
    Library library("data/books.json");
    int choice;
    
    do {
        Display::displayMenu();
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                Display::addBookMenu(library);
                break;
            case 2:
                Display::searchBookMenu(library);
                break;
            case 3:
                Display::borrowBookMenu(library);
                break;
            case 4:
                Display::returnBookMenu(library);
                break;
            case 5:
                library.displayAllBooks();
                break;
            case 6:
                Display::removeBookMenu(library);
                break;
            case 0:
                std::cout << "Exiting. Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
    
    return 0;
}