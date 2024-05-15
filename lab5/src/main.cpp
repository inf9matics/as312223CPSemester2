#include "book.h"

#include <iostream>

int main() {
    Book *book;
    book = new Book{0, "The great purge"};
    std::cout << book->LendableReal::getFullTitle() << "\n";
    std::cout << book->LendableDigital::getFullTitle() << "\n";

    std::cout << book->getFullTitle() << "\n";

    return 0;
}