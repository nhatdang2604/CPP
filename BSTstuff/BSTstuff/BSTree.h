#pragma once

template <class T>
struct BSTNode
{
	T data;
	int id;
	BSTNode<T> *left;
	BSTNode<T> *right;
};


template <class T>
class BSTree
{
private: 
	BSTNode<T> *root;
public:
	BSTree();
	~BSTree();
};

