#include "Random.h"

bool Random::_seeded = false;
void Random::getSeed() {
	srand((unsigned int)time(NULL));
	this->_seeded = true;
}

int Random::nextInt() {
	if (!this->_seeded)
		getSeed();
	return rand();
}

int Random::nextInt(const int& ceiling) {
	return this->nextInt() % ceiling;
}

int Random::nextInt(const int& left, const int& right) {
	int delta = right - left + 1;
	return this->nextInt() % delta + left;
}


