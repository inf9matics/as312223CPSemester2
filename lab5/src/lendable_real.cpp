#include "lendable_real.h"

#include <iostream>

LendableReal::LendableReal(int id, std::string title) {
    std::cout << "LendableReal Constructor\n";
    this->id = id;
    this->title = title;
}

std::string LendableReal::getFullTitle() {
    return std::to_string(this->id) + ": [Real]" + this->title;
}