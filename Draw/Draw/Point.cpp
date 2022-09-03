#include "Point.h"
#include <math.h>

Point& Point::operator=(const Point& other) {
	this->x = other.x;
	this->y = other.y;
	return *this;
}

Point::Point(const int& inX, const int& inY) {
	this->x = inX;
	this->y = inY;
}

Point::Point(const Point& other) {
	*this = other;
}

double Point::distance(const Point& other) {
	return sqrt((this->x - other.x)*(this->x - other.x) + (this->y - other.y)*(this->y - other.y));
}

double Point::getX() {
	return this->x;
}

double Point::getY() {
	return this->y;
}

istream& operator >> (istream& inDevice, Point& other) {
	cout << "Moi nhap x: ";
	inDevice >> other.x;
	cout << "Moi nhap y: ";
	inDevice >> other.y;
	return inDevice;
}

Point::~Point() {
}
