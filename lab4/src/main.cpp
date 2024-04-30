#include <iostream>
#include <vector>

#include "book.h"
#include "song.h"

int main() {
    int n = 10;
    std::vector<Lendable *> books;
    for(int i{1}; i<=n; i++) {
        books.emplace_back(new Book{i, std::to_string(2*i), std::to_string(3*i), std::to_string(4*i)});
    }
    std::vector<Lendable *>::iterator booksIterator = books.begin();
    while(booksIterator != books.end()) {
        (*booksIterator)->show();
        std::cout << "\n";
        booksIterator++;
    }

    Lendable *song;
    song = new Song{42, "Song42", "John", "Lorem ipsum dolor"};
    dynamic_cast<Song *>(song)->sing();
    std::cout << "\n";

    return 0;
}