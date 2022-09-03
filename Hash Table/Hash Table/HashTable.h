#pragma once
#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_
#include<vector>
#include<list>
#include<iostream>
using namespace std;

class HashTable {
public:
	HashTable(const int&);
	~HashTable();

	int getSize();
	int getNumberOfBuckets();
	int getKey(const int&);

	void insert(const int&);
	void removeAll(const int&);
	void remove(const int&);
	void display();
private:
	int numberOfBuckets;
	list<int>* table;

	int _getSize();
	int _getNumberOfBuckets();
	int _getKey(const int&);

	void _insert(const int&);
	void _removeAll(const int&);
	void _remove(const int&);
	void _display();
};


#endif // !_HASHTABLE_H



