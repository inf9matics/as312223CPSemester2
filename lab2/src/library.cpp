#include <iostream>
#include <ostream>

#include "library.h"
#include "song.h"

Library::Library() {}

void Library::add(Song song) {
    this->songs.push_back(song);
}

std::ostream& Library::print(std::ostream &ostream) {
    std::vector<Song>::iterator songsIterator = this->songs.begin();
    while(songsIterator != this->songs.end()) {
        ostream.write(songsIterator->getName().c_str(), songsIterator->getName().size());
        songsIterator++;
    }
    return ostream;
}

Library& Library::operator+(Song &song) {
    this->add(song);
    return *this;
}

// std::ostream& Library::operator<<(std::ostream &ostream, Library const &library) {
//     return this->print(ostream);
// }