#pragma once
#ifndef  _CIRCLE_H_
#define _CIRCLE_H_
#define PI 3.14

#include "Figure.h"
class Circle: public Figure{
private: 
	double radius;
	Point* center = nullptr;
public:
	Circle(const double&, const Point&);
	~Circle();

	string type();
	Point getCenter();
	double getRadius();
	double area();
	double perimeter();
	void input(istream&);
};


#endif // ! _CIRCLE_H_


