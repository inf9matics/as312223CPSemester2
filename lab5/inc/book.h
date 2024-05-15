#ifndef BOOK_H
#define BOOK_H

#include "lendable_real.h"
#include "lendable_digital.h"

class Book : public LendableReal, public LendableDigital {
    public:
    Book(int id, std::string title);
};

#endif