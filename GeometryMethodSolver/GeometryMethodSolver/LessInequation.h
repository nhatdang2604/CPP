#pragma once
#ifndef _LESS_INEQUATION_H_
#define _LESS_INEQuATION_H_

#include "Point.h"
#include <iostream>

#define EPSILON 1e-6


//Form: a*x + b*y <= c (a, b, c is natural number)
class LessInequation {
private:
	int _a, _b, _c;	//the coefficients

public: //getters and setters

	//Getters
	int a() { return _a; }
	int b() { return _b; }
	int c() { return _c; }

	//Setters
	LessInequation setA(int a) { _a = a; return *this; }
	LessInequation setB(int b) { _b = b; return *this; }
	LessInequation setC(int c) { _c = c; return *this; }

private:	//utitlites

	//Calculate the left hand side of the inequation
	double getLeftValue(Point point) {
		return 1.0*_a*point.x() + 1.0*_b*point.y();
	}

public:

	//Check if a point is inside the domain
	bool isInside(Point point) {
		if (std::abs(getLeftValue(point) - _c) < EPSILON) {
			return true;
		}

		return false;
	}


	//Get the intersection point from two line which build from the less inequations
	//	by using Crammer's principle
	static Point* getIntersection(LessInequation a, LessInequation b) {

	
		double delta = a.a() * b.b() - a.b() * b.a();

		//If the equation have infinite solution or no solution => return null
		if (delta <= EPSILON) return nullptr;

		//The equation have 1 solution => solved
		double delta1 = a.c() * b.b() - b.c() * b.a();
		double delta2 = a.a() * b.c() - a.c() * b.a();

		return new Point(1.0*delta1 / delta, 1.0*delta2 / delta);
	}

	//Check if the 2 line build from the edge of 2 equations is the same
	static bool isTheSame(LessInequation a, LessInequation b) {
		
		//Check the coefficents for the result
		bool result = std::abs(((1.0)*a.a() / (1.0)*b.a()) - ((1.0)*a.b() / (1.0)*b.b())) <= EPSILON;
		result &= std::abs(((1.0)*a.b() / (1.0)*b.b()) - ((1.0)*a.c() / (1.0)*b.c())) <= EPSILON;

		return result;
	}

public:

	LessInequation(int a, int b, int c) {
		_a = a;
		_b = b;
		_c = c;
	};

	LessInequation() {
		//do nothing
	};

	~LessInequation() {
		//do nothing
	}
};


#endif // !_INEQUATION_H_



