#pragma once
#ifndef _BTREE_H_
#define _BTREE_H_

#include <iostream>
using namespace std;

struct BNode {
	//node[0] <= key[0] <= node[1] <= key[1] ... <= node[n-1] <= key[n-1] <= node[n]

	int n;		//number of keys which BNode has
	int *key;	//keys of BNodes: key[0] <= key[1] <= key[2] <= .... <= key[n-1]
	BNode *node;//sub-tree: there are n + 1 sub-tree
	bool leaf;	//return true if the current node is a leaf, else return false
};

/* return the node->key[index] */
struct DataSearch {
	BNode *node;
	int index;
};

class BTree {
private:
	
	BNode* root = nullptr;	//The root is always in the main memory => Disk-read on the root is NEVER required.
							//The disk-write of the root is required, whenever the root node is changed
	DataSearch* BTreeSearch(BNode*, int);

public:
	BTree() {
		root = new BNode;
		root->leaf = true;
		root->n = 0;
		//disk-write(root)
	}


};

#endif // !_BTREE_H_
