#pragma once
#ifndef _FULLNAME_H_
#define _FULLNAME_H_

#include <string>

class Fullname {
private:
	std::string _firstname;
	std::string _middlename;
	std::string _lastname;
public:
	std::string toString();
public:
	Fullname(const std::string&, const std::string&, const std::string&);
	~Fullname();
};

#endif // !_FULLNAME_H_



