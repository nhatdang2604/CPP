#pragma once
#ifndef  _RANDOM_H_
#define _RANDOM_H_

#include <iostream>
#include <time.h>

class Random {
private:
	static bool _seeded;
	void getSeed();
public:
	int nextInt();
	int nextInt(const int&);
	int nextInt(const int&, const int&);

public:
	Random() {
		if (!this->_seeded)
			getSeed();
	};
	~Random() {
		//do nothing
	}
};

#endif // ! _RANDOM_H_



