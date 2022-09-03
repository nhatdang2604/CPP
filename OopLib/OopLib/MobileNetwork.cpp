#include "MobileNetwork.h"


std::string MobileNetwork::name() {
	return this->_name;
}

std::vector <std::string> MobileNetwork::prefixes() {
	return this->_prefixes;
}

MobileNetwork::MobileNetwork(const std::string& initName, const std::vector <std::string>& initPrefixes) {
	this->_name = initName;
	this->_prefixes = initPrefixes;
}


MobileNetwork::MobileNetwork() {
	// do nothing
}


MobileNetwork::~MobileNetwork() {
	// do nothing	
}
