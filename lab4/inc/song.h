#ifndef SONG_H
#define SONG_H

#include "lendable.h"

class Song : public Lendable {
      protected:
    std::string author;
    std::string lyrics;

    Song &setAuthor(std::string author);
    Song &setLyrics(std::string lyrics);

      public:
    Song(long id, std::string title, std::string author, std::string lyrics);

    Song &sing();

    std::string getLyrics();
};

#endif