#pragma once
#ifndef  _RANDOMYEAR_H_
#define _RANDOMYEAR_H_
using namespace std;

#include<time.h>
#include<random>
#include<vector>

int randomizeAnIntegerFromRange(const int&, const int&);
vector<int> randomizeYears(const int&, const int&);
bool isLeapYear(const int&);
int countLeapYears(const vector<int>&);

#endif

