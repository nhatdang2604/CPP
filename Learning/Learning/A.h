#pragma once
#ifndef _A_H_
#define _A_H

#include "B.h"
#include <iostream>
class A {
public:
	static char type() {
		return 'A';
	}

	static void call() {
		std::cout << B::type() << std::endl;
	}
};

#endif // !_A_H_



