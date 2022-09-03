#pragma once
#ifndef _TELEPHONE_H_
#define _TELEPHONE_H_

#include "MobileNetwork.h"


class Telephone {
private:
	MobileNetwork _network;
	std::string _prefix;
	std::string _number;
public:
	MobileNetwork network();
	std::string number();
	std::string toString();
public:
	Telephone(const MobileNetwork&, const std::string&, const std::string&);
	~Telephone();
};


#endif // !_TELEPHONE_H_


