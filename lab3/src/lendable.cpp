#include "lendable.h"

#include <iostream>

Lendable::Lendable() {}

Lendable::Lendable(const Lendable& lendable) {
    *this = lendable;
}

Lendable::Lendable(Lendable&& lendable) {
    *this = lendable;
}

Lendable::Lendable(long id) {
    this->setId(id);
}

Lendable::Lendable(long id, std::string title) {
    this->setId(id).setTitle(title);
}

Lendable::Lendable(long id, std::string title, std::string author, long length) {
    this->setId(id).setTitle(title).setAuthor(author).setLength(length);
}

Lendable& Lendable::operator=(const Lendable& lendable) {
    return this->setId(lendable.id).setTitle(lendable.title).setAuthor(lendable.author).setLength(lendable.length);
}

Lendable& Lendable::operator=(Lendable&& lendable) {
    this->setId(lendable.id);
    lendable.id = NULL;

    this->setTitle(lendable.title);
    lendable.title = nullptr;

    this->setAuthor(lendable.author);
    lendable.author = nullptr;

    this->setLength(lendable.length);
    lendable.length = NULL;

    return *this;
}

Lendable& Lendable::setId(long id) {
    this->id = id;
    return *this;
}

long Lendable::getId() {
    return this->id;
}

Lendable& Lendable::setTitle(std::string title) {
    this->title = title;
    return *this;
}

std::string Lendable::getTitle() {
    return this->title;
}

Lendable& Lendable::setAuthor(std::string author) {
    this->author = author;
    return *this;
}

std::string Lendable::getAuthor() {
    return this->author;
}

Lendable& Lendable::setLength(long length) {
    this->length = length;
    return *this;
}

Lendable::~Lendable() {
    std::clog << "destructing_Lendable-" << this;
}