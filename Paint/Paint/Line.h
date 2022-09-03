#pragma once
#ifndef  _LINE_H_
#define _LINE_H_

#include "Figure.h"
#include "Point.h"

namespace figure {
	class Line : public Figure {

	private: //private attribute
		Point _start;
		Point _end;

	public:	//getter and setter
		Point start() const { return _start; };
		Point end() const { return _end; };

	public:	//override method

		bool isIn(const RECT& rect) const override {
			int topLeftX = _start.x();
			int bottomRightX = _end.x();
			if (topLeftX > bottomRightX) 
				std::swap(topLeftX, bottomRightX);
			int topLeftY = _start.y();
			int bottomRightY = _end.y();
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
			builder << "Line" << ": " << _start << " " << _end;
			return builder.str();
		};

		int type() const override {
			return TYPE_LINE;
		};

		void draw(HDC& hdc) const override {
			MoveToEx(hdc, _start.x(), _start.y(), NULL);
			LineTo(hdc, _end.x(), _end.y());
		}

		std::shared_ptr<Figure> duplicate() const override {
			return std::make_shared<Line>(*this);
		}

		void move(const Point& vector) override {
			_start.setX(_start.x() + vector.x());
			_start.setY(_start.y() + vector.y());
			_end.setX(_end.x() + vector.x());
			_end.setY(_end.y() + vector.y());
		}

	public: //static method
		static std::shared_ptr<Line> Line::parse(std::string& buffer, std::string needle = " ") {
			std::vector<std::string> tokens = Tokenizer::split(buffer, needle);
			Point start = Point::parse(tokens[0]);
			Point end = Point::parse(tokens[1]);
			return std::make_shared<Line>(start, end);
		}

	public:	//Constructor and Destructor
		Line() {
			//do nothing
		}

		Line(const Point& start, const Point& end) {
			_start = start;
			_end = end;
		}
		~Line() override {
			//do nothing
		}
	};
}

#endif // ! _LINE_H_

