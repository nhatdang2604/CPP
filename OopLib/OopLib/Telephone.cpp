#include "Telephone.h"

Telephone::Telephone(const MobileNetwork& newNetwork, const std::string& newPrefix, const std::string& newNumber) {
	this->_network = newNetwork;
	this->_prefix = newPrefix;
	this->_number = newNumber;
}

MobileNetwork Telephone::network() {
	return this->_network;
}

std::string Telephone::number() {
	return this->_number;
}

std::string Telephone::toString() {
	std::stringstream builder;
	builder << this->_network.name() << ": " << this->_prefix << this->_number;
	return builder.str();
}

Telephone::~Telephone() {
	//do nothing
}
