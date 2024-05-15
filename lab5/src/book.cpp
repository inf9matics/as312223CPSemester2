#include "book.h"

#include <iostream>

Book::Book(int id, std::string title) : LendableReal(id, title), LendableDigital(id, title) {
    std::cout << "Book Constructor\n";
}