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

    std::ostream& print(std::ostream &ostream);

    Library& operator+(Song &song);

    // std::ostream& operator<<(std::ostream &ostream, Library const &library);
};

#endif