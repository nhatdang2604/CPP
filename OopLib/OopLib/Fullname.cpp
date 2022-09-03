#include "Fullname.h"
#include <sstream>


Fullname::Fullname(const std::string& firstname, const std::string& middlename, const std::string& lastname) {
	this->_firstname = firstname;
	this->_middlename = middlename;
	this->_lastname = lastname;
}

std::string Fullname::toString() {
	std::stringstream builder;
	builder << this->_firstname << " " << this->_middlename << " " << this->_lastname;
	return builder.str();
}

Fullname::~Fullname() {
	//do nothing
}
