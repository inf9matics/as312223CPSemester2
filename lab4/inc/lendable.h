#ifndef LENDABLE_H
#define LENDABLE_H

#include <string>
#include <iostream>

class Lendable {
      protected:
    long id;
    std::string title;

    Lendable &setId(long id);
    Lendable &setTitle(std::string title);

      public:
    Lendable();
    Lendable(long id);
    Lendable(long id, std::string title);

    long getId();

    virtual std::string getTitle();

    virtual std::string getFullInfo();

    virtual Lendable &show();
};

#endif