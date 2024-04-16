#include "movie.h"

#include <iostream>

Movie::Movie() : Lendable() {}

Movie::Movie(long id) : Lendable(id) {}

Movie::Movie(long id, std::string title) : Lendable(id, title) {}

Movie::Movie(long id, std::string title, std::string author, long length) : Lendable(id, title, author, length) {}

Movie::Movie(long id, std::string title, std::string author, long length, std::string mainLead) : Lendable(id, title, author, length) {
    this->setMainLead(mainLead);
}

Movie& Movie::setMainLead(std::string mainLead) {
    this->mainLead = mainLead;
    return *this;
}

std::string Movie::getMainLead() {
    return this->mainLead;
}

Movie::~Movie() {
    std::clog << "destructing_Movie-" << this;
}