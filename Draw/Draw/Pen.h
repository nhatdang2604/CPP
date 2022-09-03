#pragma once
#ifndef  _PEN_H_
#define _PEN_H_

#include "Figure.h"
#include <windows.h>
using namespace std;

class Pen {
private:
	Figure* figureToDraw = nullptr;
	Pen();

public:
	static void getObject();
	~Pen();
};

#endif // ! _PEN_H_




