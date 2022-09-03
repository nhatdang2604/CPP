#pragma once
#ifndef _DICE_H_
#define _DICE_H_

#define NUMBER_OF_DICE_FACES 6

#include "Random.h"

class Dice {
private:
	Random rng;
	
public:
	int roll();

public:
	Dice() {
		//do nothing
	};

	~Dice() {
		//do nothing
	};
};

#endif // !_DICE_H_



