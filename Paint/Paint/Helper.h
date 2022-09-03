#pragma once
#ifndef _HELPER_H_
#define _HELPER_H_
class Helper {
public:
	//Swap top, left, right, down of a rect in correct position
	static void standardlizeRect(RECT& rect) {
		if (rect.left > rect.right) std::swap(rect.left, rect.right);
		if (rect.top > rect.bottom) std::swap(rect.top, rect.bottom);
	}

};


#endif // !_HELPER_H_


