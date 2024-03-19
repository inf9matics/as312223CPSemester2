#include <iostream>

#include "library.h"
#include "song.h"

int main() {
    Song song1{};
    Song song2{1, "Yeet", "Yeeters"};

    Library library{};
    library.add(song1);
    library + song2;
    // library + Song{32, "abc", "cba"};

    library.print(std::cout);
    std::cout << std::endl << std::endl;
    std::cout << library;
    std::cout << std::endl;
}