#pragma once
#ifndef _POINT_H_
#define _POINT_H_

//Point in 2-dimension 
class Point {

private: //attributes

	double _x, _y;

public: //getters and setters

	//Getters
	int x() { return _x; }
	int y() { return _y; }

	//Setters
	Point setX(double x) { _x = x; return *this; }
	Point setY(double y) { _y = y; return *this; }

public:

	//Compare by x, if x is equals, compare by y
	static bool compare(Point a, Point b) {
		return a.x() < b.x() || (a.x() == b.x() && a.y() < b.y());
	}

public:

	Point()
	{
		//do nothing
	}

	Point(Point* point) {
		_x = point->x();
		_y = point->y();
	}

	Point(double x, double y) {
		_x = x;
		_y = y;
	}

	~Point()
	{
	}
};

#endif // !_POINT_H_




