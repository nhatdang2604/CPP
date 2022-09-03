#pragma once
#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

#include "Point.h"
#include "Figure.h"

void drawRectangle(HDC& hdc, int left, int top, int right, int bottom) {
	Rectangle(hdc, left, top, right, bottom);
}

namespace figure {
	class Rectangle : public Figure {

	protected://protected attribute
		Point _topLeft;
		Point _bottomRight;

	public:	//getter and setter
		Point topLeft() const { return _topLeft; };
		Point bottomRight() const { return _bottomRight; };

	public:	//override method
		
		bool isIn(const RECT& rect) const override {
			int topLeftX = _topLeft.x();
			int bottomRightX = _bottomRight.x();
			if (topLeftX > bottomRightX)
				std::swap(topLeftX, bottomRightX);
			int topLeftY = _topLeft.y();
			int bottomRightY = _bottomRight.y();
			if (topLeftY > bottomRightY)
				std::swap(topLeftY, bottomRightY);

			if (topLeftX >= rect.left &&
				bottomRightX <= rect.right &&
				topLeftY >= rect.top &&
				bottomRightY <= rect.bottom) {
				return true;
			}

			return false;
		}

		std::string toString() const override {
			std::stringstream builder;
			builder << "Rectangle" << ": " << _topLeft << " " << _bottomRight;
			return builder.str();
		};

		int type() const override {
			return TYPE_RECTANGLE;
		};

		void draw(HDC& hdc) const override {
			drawRectangle(hdc,
				_topLeft.x(),
				_topLeft.y(),
				_bottomRight.x(),
				_bottomRight.y()
			);
		}

		std::shared_ptr<Figure> duplicate() const override {
			return std::make_shared<Rectangle>(*this);
		}

		void move(const Point& vector) override {
			_topLeft.setX(_topLeft.x() + vector.x());
			_topLeft.setY(_topLeft.y() + vector.y());
			_bottomRight.setX(_bottomRight.x() + vector.x());
			_bottomRight.setY(_bottomRight.y() + vector.y());
		}

	public: //static method
		static std::shared_ptr<Rectangle> parse(std::string& buffer, std::string needle = " ") {
			std::vector<std::string> tokens = Tokenizer::split(buffer, needle);
			Point topLeft = Point::parse(tokens[0]);
			Point bottomRight = Point::parse(tokens[1]);
			return std::make_shared<Rectangle>(topLeft, bottomRight);
		};

	public:	//constructor and destructor
		Rectangle() {
			//do nothing
		};

		Rectangle(const Point& topLeft, const Point& bottomRight) {
			_topLeft = topLeft;
			_bottomRight = bottomRight;
		};

		~Rectangle() override {
			//do nothing
		};
	};
}


#endif // !_RECTANGLE_H_


