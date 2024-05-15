#include "lendable_digital.h"

#include <iostream>

LendableDigital::LendableDigital(int id, std::string title) {
    std::cout << "LendableDigital Constructor\n";
    this->id = id;
    this->title = title;
}

// std::string LendableDigital::getFullTitle() {
//     return std::to_string(this->id) + ": [Digital]" + this->title;
// }