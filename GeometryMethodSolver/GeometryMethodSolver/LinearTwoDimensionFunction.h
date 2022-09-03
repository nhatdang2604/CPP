#pragma once
#ifndef _LINEAR_TWO_DIMENSION_FUNCTION_H_
#define _LINEAR_TWO_DIMENSION_FUNCTION_H_

#include "Point.h"

//Function: f(x,y) = a*x + b*y 
class LinearTwoDimensionFunction {

private:
	int _a, _b;	//coefficients

public:	//getters and setters

		//Getters
	int a() { return _a; }
	int b() { return _b; }

	//Setters
	LinearTwoDimensionFunction setX(double a) { _a = a; return *this; }
	LinearTwoDimensionFunction setY(double b) { _b = b; return *this; }

public:	//API

	//Calculate the function
	double calc(Point point) {
		return (1.0)*_a*point.x() + (1.0)*_b*point.y();
	}

public:

	LinearTwoDimensionFunction(int a, int b)
	{
		_a = a;
		_b = b;
	}

	LinearTwoDimensionFunction()
	{
		//do nothing
	}

	~LinearTwoDimensionFunction()
	{
		//do nothing
	}
};

#endif // !_LINEAR_TWO_DIMENSION_FUNCTION_H_


