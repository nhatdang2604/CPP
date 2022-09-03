#pragma once
#ifndef _PEN_H_
#define _PEN_H

#include "Paint.h"
#include "Figure.h"
#include "Line.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Circle.h"
#include "Square.h"
#include "Point.h"
#include <vector>

#define SIGN "This is a Paint project file"

struct Shape {
	
	//If use move/cut/delete (process make the old shape changed)
	//	=> executedFrom = the old shape
	Shape* executedFrom;

	//style
	int iStyle;
	int cWidth;
	COLORREF color;

	//figure
	std::shared_ptr<figure::Figure> figure;

	//If (!isValid)
	//	=> cannot be drawn anymore
	bool isValid;

};

std::vector<Shape> states;

class Pen {

private:	//private attribute

	//style
	int _iStyle;
	int _cWidth;
	COLORREF _color;

	//Style for drawing
	HPEN _hPen;

	//The current shape which would be drawed
	std::shared_ptr<figure::Figure> _figure;

public:	//Getter and setter
	void setFigure(std::shared_ptr<figure::Figure> figure) {
		_figure = figure;
	}

	void setStyle(HDC& hdc, int iStyle, int cWidth, COLORREF color) {
		if (_hPen && (_iStyle != iStyle || _cWidth != cWidth || _color != color)) {
			DeleteObject(_hPen);
			_hPen = nullptr;
			_iStyle = iStyle;
			_cWidth = cWidth;
			_color = color;
			_hPen = CreatePen(iStyle, cWidth, color);
			SelectObject(hdc, _hPen);
		}
	};

public:	//static method

	//draw all shape in shapes
	static void drawAll(HDC& hdc, std::vector<Shape> shapes = states) {
		std::vector<Pen> pens(shapes.size());
		for (unsigned int i = 0; i < shapes.size(); ++i) {
			pens[i]._figure = shapes[i].figure;
			pens[i].setStyle(hdc, shapes[i].iStyle, shapes[i].cWidth, shapes[i].color);
			if (shapes[i].isValid) pens[i]._figure->draw(hdc);
		}
	}


public:	//normal public method

	void draw(HDC& hdc) {
		if (!_figure) return;
		_figure->draw(hdc);
	}

	/*
	//Draw all shapes in states
	void drawAll(HDC& hdc) {

		//Save current state
		int savedIStyle = _iStyle;
		int savedCWidth = _cWidth;
		COLORREF savedColor = _color;
		std::shared_ptr<figure::Figure> savedFigure = _figure;

		for (Shape i : states) {
			_figure = i.figure;
			setStyle(hdc, i.iStyle, i.cWidth, i.color);
			if (i.isValid)_figure->draw(hdc);
		};
		
		//Restore to current state
		_figure = savedFigure;
		setStyle(hdc, savedIStyle, savedCWidth, savedColor);
	}*/

	//Save the drawn shape into states
	void saveShape() const {
		if (!_figure) return;
		Shape shape;
		shape.executedFrom = nullptr;
		shape.iStyle = _iStyle;
		shape.cWidth = _cWidth;
		shape.color = _color;
		shape.figure = _figure;
		shape.isValid = true;
		states.push_back(shape);
	}

public:	//constructor and destructor
	Pen() {
		//do nothing
	}

	Pen(HDC& hdc,
		int iStyle = PS_DASHDOT,
		int cWidth = 3,
		COLORREF color = RGB(255, 0, 0)) {

		_iStyle = iStyle;
		_cWidth = cWidth;
		_color = color;
		_figure = nullptr;
		_hPen = CreatePen(iStyle, cWidth, color);
		SelectObject(hdc, _hPen);
	}


	~Pen() {
		if (_hPen) DeleteObject(_hPen);
		_hPen = nullptr;
	}
};

#endif // !_PEN_H_