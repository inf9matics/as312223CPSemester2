#ifndef LENDABLE_DIGITAL_H
#define LENDABLE_DIGITAL_H

#include <string>

#include "lendable_base.h"

class LendableDigital : virtual public LendableBase {
      public:
	LendableDigital(int id, std::string title);

	// std::string getFullTitle();
};

#endif