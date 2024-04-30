#ifndef BOOK_H
#define BOOK_H

#include "lendable.h"

class Book : public Lendable {
      protected:
    std::string author;
    std::string series;

    Book &setAuthor(std::string author);
    Book &setSeries(std::string series);

      public:
    Book();
    Book(long id);
    Book(long id, std::string title);
    Book(long id, std::string title, std::string series, std::string author);

    std::string getTitle();

    std::string getFullInfo();

    Book &show();
};

#endif