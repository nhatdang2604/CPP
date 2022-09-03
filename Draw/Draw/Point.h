#pragma once
#ifndef  _POINT_H_
#define _POINT_H_

#include <iostream>
using namespace std;

class Point {
private:
	double x, y;
public:
	Point(const int&, const int&);
	Point(const Point&);
	~Point();

	double getX();
	double getY();
	double distance(const Point&);

	friend istream& operator >> (istream&, Point&);
	Point& operator=(const Point&);
};



#endif // ! _POINT_H_



