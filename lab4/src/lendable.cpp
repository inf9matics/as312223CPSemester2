#include "lendable.h"

Lendable::Lendable() {}

Lendable::Lendable(long id) {
    this->setId(id);
}

Lendable::Lendable(long id, std::string title) {
    this->setId(id).setTitle(title);
}

Lendable &Lendable::setId(long id) {
    this->id = id;
    return *this;
}

Lendable &Lendable::setTitle(std::string title) {
    this->title = title;
    return *this;
}

long Lendable::getId() {
    return this->id;
}

std::string Lendable::getTitle() {
    return this->title;
}

std::string Lendable::getFullInfo() {
    return ("[" + std::to_string(this->id) + "] " + this->getTitle());
}

Lendable &Lendable::show() {
    std::cout << this->getFullInfo() << "\n";
    return *this;
}