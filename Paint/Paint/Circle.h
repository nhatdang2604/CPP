#pragma once
#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "Ellipse.h"
#include "Point.h"
#include "Figure.h"

namespace figure {
	class Circle : public Ellipse {
	
	/*	Parent class already had public getters setters
	public:	//getter and setter
		Point topLeft() const { return _topLeft; };
		Point bottomRight() const { return _bottomRight; };
	*/

	public:	//override method

		std::string toString() const override {
			std::stringstream builder;
			builder << "Circle" << ": " << _topLeft << " " << _bottomRight;
			return builder.str();
		};
		int type() const override {
			return TYPE_CIRCLE;
		};

		std::shared_ptr<Figure> duplicate() const override {
			return std::make_shared<Circle>(*this);
		}

		//No need, parent class already have
		//void draw(HDC& hdc)
		//bool isIn(const Rect& rect)
		//void move(const Point&)

	public: //static method
		static std::shared_ptr<Circle> parse(std::string& buffer, std::string needle = " ") {
			std::vector<std::string> tokens = Tokenizer::split(buffer, needle);
			Point topLeft = Point::parse(tokens[0]);
			Point bottomRight = Point::parse(tokens[1]);
			return std::make_shared<Circle>(topLeft, bottomRight);
		};

	public:	//constructor and destructor

		Circle() {
			//do nothing
		};

		Circle(const Point& topLeft, const Point& bottomRight) {
			_topLeft = topLeft;
			_bottomRight = bottomRight;
		};

		~Circle() override {
			//do nothing
		};
	};
}

#endif // !_CIRCLE_H_

