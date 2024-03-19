#include <iostream>
#include <ostream>

#include "library.h"
#include "song.h"

Library::Library() {}

void Library::add(Song song) {
    this->songs.push_back(song);
}

void Library::print(std::ostream &ostream) {
    std::vector<Song>::iterator songsIterator = this->songs.begin();
    while(songsIterator != this->songs.end()) {
        ostream.write(songsIterator->getName().c_str(), songsIterator->getName().size());
        songsIterator++;
    }
}

Library& Library::operator+(Song &song) {
    this->add(song);
    return *this;
}

std::ostream& operator<<(std::ostream &ostream, Library &library) {
    library.print(ostream);
    return ostream;
}