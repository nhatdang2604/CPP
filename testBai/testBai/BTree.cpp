#include "BTree.h"

DataSearch* BTree::BTreeSearch(BNode* x, int k) {
	DataSearch* result;
	if (x->leaf) return nullptr;
	int i = 0;
	for (i = 0; i < x->n && x->key[i] < k; ++i);
	
}