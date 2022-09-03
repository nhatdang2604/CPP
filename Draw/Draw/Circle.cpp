#include "Circle.h"

Circle::Circle(const double& Radius, const Point& Center) {
	this->center = new Point(Center);
	this->radius = Radius;
}

Point Circle::getCenter() {
	return *this->center;
}

double Circle::getRadius() {
	return this->radius;
}

double Circle::area() {
	return PI*radius*radius;
}

double Circle::perimeter() {
	return PI * 2 * radius;
}

void Circle::input(istream& inDevice) {
	cout << "Moi nhap ban kinh: ";
	inDevice >> this->radius;
	cout << "Moi nhap toa do tam: ";
	inDevice >> *this->center;
}

string Circle::type() {
	return "CIRCLE";
}

Circle::~Circle() {
	if (this->center) delete this->center;
}
