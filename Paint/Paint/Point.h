#pragma once
#ifndef  _POINT_H_
#define _POINT_H_

#include "Tokenizer.h"
#include <iostream>
#include <vector>
#include <string>

#define MAX_CORDINATE 100

namespace figure{
	class Point {

	private://private attribute
		int _x;
		int _y;

	public:	//getter and setter

		int x() const { return _x; };
		int y() const { return _y; };
		void setX(int x) { _x = x; };
		void setY(int y) { _y = y; };

	public:	//static method

		static Point parse(std::string& buffer, std::string needle = ",") {
			std::vector<std::string> tokens = Tokenizer::split(buffer, needle);
			int x = std::stoi(tokens[0]);
			int y = std::stoi(tokens[1]);
			return Point(x, y);
		};

	public:	//overload operator

		friend std::ostream& operator <<(std::ostream& device, const Point& object) {
			device << object._x << "," << object._y;
			return device;
		};

	public:	//constructor and destructor
		Point() {
			//do nothing
		};

		Point(int x, int y) {
			this->_x = x;
			this->_y = y;
		};

		~Point() {
			//do nothing
		};
	};
};

#endif // ! _POINT_H_




