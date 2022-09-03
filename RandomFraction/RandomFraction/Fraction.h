#pragma once
#ifndef _FRACTION_H_
#define _FRACTION_H_

#include <iostream>
#include "Integer.h"

class Fraction {
private:
	long long int _numerator;
	long long int _denominator;
public:
	void print();
	void setNumerator(const int&);
	void setDenominator(const int&);
	long long int numerator();
	long long int denominator();
	void reduce();
	Fraction operator +(Fraction&);

public:
	Fraction() {
		this->_numerator = 0;
		this->_denominator = 1;
	};

	Fraction(const long long int& __numerator, const long long int& __denominator) {
		this->_numerator = __numerator;
		this->_denominator = __denominator;
	};
	~Fraction() {
		//do nothing
	};
};

#endif // !_FRACTION_H_



