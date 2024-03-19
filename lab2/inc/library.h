#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <vector>
#include <iostream>

#include "song.h"

class Library {
      protected:
    std::vector<Song> songs;

      public:
    Library();

    void add(Song song);

    void print(std::ostream &ostream);

    Library& operator+(Song &song);
    Library& operator+(Song *song);

    friend std::ostream& operator<<(std::ostream &ostream, Library &library);
};

#endif