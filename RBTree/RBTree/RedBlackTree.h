#pragma once
#ifndef  _REDBLACKTREE_H_
#define _REDBLACKTREE_H_
#include <iostream>
#include <queue>
using namespace std;

#define RED true
#define BLACK false
#define MAX(a, b) ((a)<(b)?(b):(a))

typedef bool color;

class RBNode {
private:

	//data field
	RBNode* left = nullptr;
	RBNode* right = nullptr;
	color colour;
	int heightData = 0;
	int data;
	
	RBNode* leftRotation();
	RBNode* rightRotation();
	RBNode* _insert(const int&);
	bool isRed();
	void flipColor();
	void _release();
	void _output(RBNode*);
	void printNode(RBNode*, int);
	int _height();

public:
	RBNode(const int& data, const color& colour = RED);
	~RBNode();
	RBNode* insert(const int&);
	void release();
	void output();
	int height();
};

#endif // ! _REDBLACKTREE_H_


