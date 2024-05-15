#ifndef LENDABLE_BASE_H
#define LENDABLE_BASE_H

#include <string>

class LendableBase {
      protected:
	int id;
	std::string title;

      public:
	LendableBase(){};

	std::string getFullTitle() { return "[Base] " + std::to_string(this->id) + ": " + this->title; };
};

#endif