#include <string>

#include "song.h"

Song::Song() {
    this->id = 0;

    this->name = "";
    this->artistName = "";
}

Song::Song(int id, std::string name, std::string artistName) {
    this->id = id;

    this->name = name;
    this->artistName = artistName;
}

std::string Song::getName() {
    return this->name;
}