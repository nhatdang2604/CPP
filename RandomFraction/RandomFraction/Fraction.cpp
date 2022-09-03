#include "Fraction.h"

void Fraction::setNumerator(const int& value) {
	this->_numerator = value;
}

void Fraction::setDenominator(const int& value) {
	this->_denominator = value;
}

long long int Fraction::numerator() {
	return this->_numerator;
}

long long int Fraction::denominator() {
	return this->_denominator;
}

void Fraction::reduce() {
	long long int greatestCommonDivision = Integer::gcd(this->_numerator, this->_denominator);
	this->_numerator /= greatestCommonDivision;
	this->_denominator /= greatestCommonDivision;
}

Fraction Fraction::operator+(Fraction& other) {
	long long int __numerator = this->_numerator * other.denominator() + this->_denominator * other.numerator();
	long long int __denominator = this->_denominator * other.denominator();
	return Fraction(__numerator, __denominator);
}

void Fraction::print() {
	std::cout << this->_numerator << "/" << this->_denominator;
}