#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "Library.hpp"

namespace Display {
    // Main menu display and handling
    void displayMenu();
    
    // Book management menu functions
    void addBookMenu(Library& library);
    void searchBookMenu(Library& library);
    void borrowBookMenu(Library& library);
    void returnBookMenu(Library& library);
    void removeBookMenu(Library& library);
}

#endif // DISPLAY_HPP