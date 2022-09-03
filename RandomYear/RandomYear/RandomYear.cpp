#include "RandomYear.h"

int randomizeAnIntegerFromRange(const int& lowerBound, const int& upperBound) {
	srand(unsigned int(time(NULL)));
	int delta = (upperBound - lowerBound + 1);
	return rand() % delta + lowerBound;
}

vector<int> randomizeYears(const int& n, const int& lowerBound) {
	srand(unsigned int(time(NULL)));
	int delta = RAND_MAX + 1;
	vector<int> result(n);
	for (int i = 0; i < n; ++i)
		result[i] = rand() % delta + lowerBound;
	return result;
}

bool isLeapYear(const int& year) {
	return !(year % 100) ? !(year % 400) : !(year % 4);
}

int countLeapYears(const vector<int>& years) {
	int result = 0;
	for (unsigned int i = 0; i < years.size(); ++i)
		if (isLeapYear(years[i]))
			++result;
	return result;
}