#include "Dice.h"

int Dice::roll() {
	int value = this->rng.nextInt(NUMBER_OF_DICE_FACES) + 1;
	return value;
}
