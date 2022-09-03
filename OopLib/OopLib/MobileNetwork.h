#pragma once
#ifndef  _MOBILE_NETWORK_H_
#define _MOBILE_NETWORK_H_
#include <vector>
#include <string>
#include <sstream>

class MobileNetwork {
private:
	std::string _name;
	std::vector <std::string> _prefixes;
public:
	std::string name();
	std::vector <std::string> prefixes();
public:
	MobileNetwork();
	MobileNetwork(const std::string&, const std::vector<std::string>&);
	~MobileNetwork();
};


#endif // ! _MOBILE_NETWORK_H_



