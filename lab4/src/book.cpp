#include "book.h"

Book::Book() : Lendable() {}

Book::Book(long id) : Lendable(id) {}

Book::Book(long id, std::string title) : Lendable(id, title) {}

Book::Book(long id, std::string title, std::string series, std::string author) : Lendable(id, title) {
    this->setSeries(series).setAuthor(author);
}

Book &Book::setAuthor(std::string author) {
    this->author = author;
    return *this;
}

Book &Book::setSeries(std::string series) {
    this->series = series;
    return *this;
}

std::string Book::getTitle() {
    return (this->series + ": " + this->title); 
}

std::string Book::getFullInfo() {
    return("[" + std::to_string(this->id) + "] " + this->author + ", " + this->getTitle());
}

Book &Book::show() {
    std::cout << this->getTitle();
    return *this;
}