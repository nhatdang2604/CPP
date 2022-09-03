#pragma once
#ifndef _FIGURE_H_
#define _FIGURE_H_

#include "Point.h"
#include <string.h>
using namespace std;

class Figure {
public:
	Figure();
	virtual string type() = 0;
	virtual ~Figure() = 0;
	virtual void input(istream& inDevice) = 0;
	virtual double area() = 0;
	virtual double perimeter() = 0;
};


#endif // !_FIGURE_H_

