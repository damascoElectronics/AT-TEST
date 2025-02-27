// types/Book.cpp
#include "models.hpp"

Book::Book() : id(0), title(""), author(""), year(0), available(true) {}

Book::Book(int id, const std::string& title, const std::string& author, int year)
    : id(id), title(title), author(author), year(year), available(true) {}

int Book::getId() const {
    return id;
}

std::string Book::getTitle() const {
    return title;
}

std::string Book::getAuthor() const {
    return author;
}

int Book::getYear() const {
    return year;
}

bool Book::isAvailable() const {
    return available;
}

void Book::setId(int id) {
    this->id = id;
}

void Book::setTitle(const std::string& title) {
    this->title = title;
}

void Book::setAuthor(const std::string& author) {
    this->author = author;
}

void Book::setYear(int year) {
    this->year = year;
}

void Book::setAvailable(bool available) {
    this->available = available;
}

void Book::borrow() {
    available = false;
}

void Book::returnBook() {
    available = true;
}