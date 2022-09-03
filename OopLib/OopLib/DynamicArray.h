#pragma once
#ifndef _DYNAMIC_ARRAY_H_
#define _DYNAMIC_ARRAY_H_

#include <iostream>
#include <iomanip>
using namespace std;

#define BUFFER_FACTOR 2
#define DEFAULT_BUFFER_SIZE 1

template<class T>
class DynamicArray {
private:
	int _bufferSize;
	int _size;
	T* _a;
public:
	int bufferSize();
	int size();
	void push_back(const T&);
public:
	template<class U>
	friend ostream& operator<<(ostream&, DynamicArray<U>&);

	const T& operator[](const int&);
	const DynamicArray<T>& operator=(const DynamicArray<T>&);
public:
	DynamicArray();
	DynamicArray(const DynamicArray<T>&);
	DynamicArray(const int&);

	~DynamicArray();
};

template<class T>
const T& DynamicArray<T>::operator[](const int& index) {
	if (index < this->_size && index >= 0) {
		return *(this->_a + index);
	}
	else {
		throw exception("Chu y: Khong duoc phep truy cap vao vung nho nam ngoai kich thuoc!\n");
	}
}

template<class T>
const DynamicArray<T>& DynamicArray<T>::operator =(const DynamicArray<T>& other) {
	if (this->_a) {
		delete[]this->_a;
		this->_a = nullptr;
	}
	this->_bufferSize = other._bufferSize;
	this->_size = other._size;
	this->_a = new T[this->_bufferSize];
	if (!this->_a) {
		cout << "Cap phat bo nho that bai!\n";
		this->_size = 0;
		this->_bufferSize = 0;
	}
	else {
		memcpy((T*)this->_a, (T*)other._a, this->_bufferSize * sizeof(T));
	}
	return *this;
}

template<class T>
DynamicArray<T>::DynamicArray() {
	this->_a = nullptr;
	this->_bufferSize = DEFAULT_BUFFER_SIZE;
	this->_size = 0;
	this->_a = new T[this->_bufferSize];
	if (!this->_a) {
		cout << "Cap phat bo nho that bai!\n";
		this->_bufferSize = 0;
		this->_size = 0;
	}
}

template<class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& other) {
	*this = other;
}

template<class T>
DynamicArray<T>::DynamicArray(const int& size) {
	this->_bufferSize = size*BUFFER_FACTOR;
	this->_size = size;
	this->_a = new T[this->_bufferSize];
	if (!this->_a) {
		cout << "Cap phat bo nho that bai!\n";
		this->_bufferSize = 0;
		this->_size = 0;
	}
}

template<class T>
int DynamicArray<T>::size() {
	return this->_size;
}

template<class T>
int DynamicArray<T>::bufferSize() {
	return this->_bufferSize;
}

template<class T>
void DynamicArray<T>::push_back(const T& value) {

	//realloc when the memory is full
	if (this->_size == this->_bufferSize) {
		T* tempMemory = nullptr;
		this->_bufferSize *= BUFFER_FACTOR;
		tempMemory = new T[this->_bufferSize];
		if (!tempMemory) {
			cout << "Khong con du bo nho de them phan tu moi!\n";
			return;
		}
		memcpy((T*)tempMemory, (T*)this->_a, sizeof(T)*this->_size);
		delete[]this->_a;
		this->_a = tempMemory;
	}
	this->_a[this->_size] = value;
	++this->_size;
}


template<class T>
DynamicArray<T>::~DynamicArray() {
	if (this->_a) {
		delete[]this->_a;
	}
}


template<class U>
ostream& operator<<(ostream& device, DynamicArray<U>& output) {
	for (int i = 0; i < output.size(); ++i) {
		device << output[i] << " ";
	}
	return device;
}

#endif // !_DYNAMIC_ARRAY_H_
