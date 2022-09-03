#pragma once
#ifndef _SQUARE_H_
#define _SQUARE_H_

#include "Rectangle.h"
#include "Point.h"
#include "Figure.h"

namespace figure {
	class Square : public Rectangle {

		/*	Parent class already had public getters setters
		public:	//getter and setter
		Point topLeft() const { return _topLeft; };
		Point bottomRight() const { return _bottomRight; };
		*/

	public:	//override method

		std::string toString() const override {
			std::stringstream builder;
			builder << "Square" << ": " << _topLeft << " " << _bottomRight;
			return builder.str();
		};
		int type() const override {
			return TYPE_SQUARE;
		};

		std::shared_ptr<Figure> duplicate() const override {
			return std::make_shared<Square>(*this);
		}

		//No need, parent class already have
		//void draw(HDC& hdc)
		//bool isIn(const Rect& rect)
		//void move(const Point&)


	public: //static method

		static std::shared_ptr<Square> parse(std::string& buffer, std::string needle = " ") {
			std::vector<std::string> tokens = Tokenizer::split(buffer, needle);
			Point topLeft = Point::parse(tokens[0]);
			Point bottomRight = Point::parse(tokens[1]);
			return std::make_shared<Square>(topLeft, bottomRight);
		};

	public:	//constructor and destructor

		Square() {
			//do nothing
		};

		Square(const Point& topLeft, const Point& bottomRight) {
			_topLeft = topLeft;
			_bottomRight = bottomRight;
		};

		~Square() override {
			//do nothing
		};
	};
}

#endif // !



