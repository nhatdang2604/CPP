#pragma once
#ifndef _B_H_
#define _B_H_

#include "A.h"
#include <iostream>
class B {
public:
	static char type() {
		return 'B';
	}

	static void call() {
		std::cout << A::type() << std::endl;
	}
};

#endif // !_B_H_


