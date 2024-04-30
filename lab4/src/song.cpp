#include "song.h"

Song::Song(long id, std::string title, std::string author, std::string lyrics) : Lendable(id, title) {
    this->setAuthor(author).setLyrics(lyrics);
}

Song &Song::setAuthor(std::string author) {
    this->author = author;
    return *this;
}

Song &Song::setLyrics(std::string lyrics) {
    this->lyrics = lyrics;
    return *this;
}

Song &Song::sing() {
    std::cout << this->getLyrics();
    return *this;
}

std::string Song::getLyrics() {
    return this->lyrics;
}