#ifndef MOVIE_H
#define MOVIE_H

#include "lendable.h"

class Movie : public Lendable {
      protected:
    std::string mainLead;

      public:
    Movie();
    Movie(Movie& movie);
    Movie(long id);
    Movie(long id, std::string title);
    Movie(long id, std::string title, std::string author, long length);
    Movie(long id, std::string title, std::string author, long length, std::string mainLead);

    Movie& setMainLead(std::string mainLead);
    std::string getMainLead();

    ~Movie();
};

#endif