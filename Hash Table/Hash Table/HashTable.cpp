#include "HashTable.h"



HashTable::HashTable(const int& size) {
	numberOfBuckets = size;
	table = new list<int>[size];
}

HashTable::~HashTable() {
	if (table) delete[]table;
}

int HashTable::_getSize() {
	int size = 0;
	for (int i = 0; i < numberOfBuckets; ++i) {
		size += table[i].size();
	}
	return size;
}

int HashTable::getSize() {
	return _getSize();
}

int HashTable::_getNumberOfBuckets() {
	return numberOfBuckets;
}

int HashTable::getNumberOfBuckets() {
	return _getNumberOfBuckets();
}

int HashTable::_getKey(const int& value) {
	return value % numberOfBuckets;
}

int HashTable::getKey(const int& value) {
	return _getKey(value);
}

void HashTable::_insert(const int& value) {
	int index = getKey(value);
	this->table[index].push_front(value);
}

void HashTable::insert(const int& value) {
	this->_insert(value);
}

void HashTable::_removeAll(const int& value) {
	int index = getKey(value);
	this->table[index].remove(value);
}

void HashTable::removeAll(const int& value) {
	this->_removeAll(value);
}

void HashTable::_remove(const int& value) {
	int index = getKey(value);
	for (list<int>::iterator i = this->table[index].begin(); i != this->table[index].end(); ++i) {
		if (*i == value) {
			this->table[index].erase(i);
			break;
		}
	}
}

void HashTable::remove(const int& value) {
	this->_remove(value);
}

void HashTable::_display() {
	for (int i = 0; i < numberOfBuckets; ++i) {
		cout << i;
		for (auto i : table[i]) {
			cout << " -> " << i;
		}
		cout << endl;
	}
}

void HashTable::display() {
	this->_display();
}


