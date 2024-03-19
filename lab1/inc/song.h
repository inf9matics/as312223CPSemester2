#ifndef SONG_H
#define SONG_H

#include <string>

class Song {
      private:
    int id;

    std::string name;
    std::string artistName;

      public:
    Song();
    Song(int id, std::string name, std::string artistName);

    std::string getName();
};

#endif