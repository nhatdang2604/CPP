#pragma once
#ifndef _SOLVER_H_
#define _SOLVER_H_

#include <vector>
#include <iostream>
#include "LessInequation.h"
#include "LinearTwoDimensionFunction.h"

class Solver {

private:
	std::vector<Point> _extremePoints;
	std::vector<LessInequation> _inequations;
	LinearTwoDimensionFunction _function;

public:

	//Read the input from user
	Solver readFromUser() {

		int n;
		int a, b, c;
		std::cin >> n;
		while (n--) {
			std::cin >> a >> b >> c;
			_inequations.push_back(LessInequation(a, b, c));
		}
		
		std::cin >> a >> b;
		_function = LinearTwoDimensionFunction(a, b);

		return *this;
	}

	//Get all the extreme points from the inequations
	std::vector<Point> getExtremePoints() {
		
		//clear the data from the past extreme points
		_extremePoints.clear();

		//Holding all the intersect point fof each pair of line
		std::vector<Point*> intersectPoints;

		//Get all the intersection points for each pair of line
		int size = _inequations.size();
		for (int i = 0; i < size; ++i) {
			for (int j = i + 1; j < size; ++j) {
				intersectPoints.push_back(LessInequation::getIntersection(_inequations[i], _inequations[j]));
			}
		}

		//Check if the intersect point is inside ALL the domain create by all the inequations
		for (Point* intersectPoint : intersectPoints) {

			bool isInside = true;
			for (LessInequation inequation : _inequations) {

				//If there is any inequations, which doesn't contain the intersect point
				//	=> check the intersect point's flag as false, then break the inner loop for optimizing
				if (!inequation.isInside(*intersectPoint)) {
					isInside = false;
					break;
				}
			}

			//Mark if the intersect point is an extreme point
			if (isInside) {
				_extremePoints.push_back(Point(intersectPoint));
			}
		}

		//Clear data to prevent memory leaking
		for (Point* point : intersectPoints) {
			delete point;
		}

		return _extremePoints;
	}

	//

public:

	Solver() {
		//do nothing
	}
	~Solver() {
		//do nothing
	}
};

#endif // !_SOLVER_H_




