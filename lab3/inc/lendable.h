#ifndef LENDABLE_H
#define LENDABLE_H

#include <string>

class Lendable {
      protected:
    long id;

    std::string title;
    std::string author;
    
    long length;

      public:
    Lendable();
    Lendable(const Lendable& lendable);
    Lendable(Lendable&& lendable);
    Lendable(long id);
    Lendable(long id, std::string title);
    Lendable(long id, std::string title, std::string author, long length);

    Lendable& operator=(const Lendable& lendable);
    Lendable& operator=(Lendable&& lendable);

    Lendable& setId(long id);
    long getId();

    Lendable& setTitle(std::string title);
    std::string getTitle();

    Lendable& setAuthor(std::string author);
    std::string getAuthor();

    Lendable& setLength(long length);
    long getLength();

    ~Lendable();
};

#endif