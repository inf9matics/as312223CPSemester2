#ifndef LENDABLE_REAL_H
#define LENDABLE_REAL_H

#include <string>

#include "lendable_base.h"

class LendableReal : virtual public LendableBase {
      public:
	LendableReal(int id, std::string title);

	std::string getFullTitle();
};

#endif