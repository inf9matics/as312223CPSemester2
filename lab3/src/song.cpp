#include <string>
#include <iostream>

#include "song.h"

Song::Song() : Lendable() {}

Song::Song(long id) : Lendable(id) {}

Song::Song(long id, std::string title, std::string author, long length) : Lendable(id, title, author, length) {}

Song::Song(long id, std::string title, std::string author, long length, std::string album) : Lendable(id, title, author, length) {
    this->setAlbum(album);
}

Song::Song(long id, std::string title, std::string author, long length, int bpm) : Lendable(id, title, author, length) {
    this->setBpm(bpm);
}

Song& Song::setBpm(int bpm) {
    this->bpm = bpm;
    return *this;
}

int Song::getBpm() {
    return this->bpm;
}

Song& Song::setAlbum(std::string album) {
    this->album = album;
    return *this;
}

std::string Song::getAlbum() {
    return this->album;
}

Song::~Song() {
    std::clog << "destructing_Song-" << this;
}