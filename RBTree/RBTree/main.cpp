#include "RedBlackTree.h"
int main() {
	RBNode* tree = nullptr;
	tree = tree->insert(1);
	tree = tree->insert(-1);
	tree = tree->insert(2);
	tree = tree->insert(2);
	tree = tree->insert(2);
	tree = tree->insert(-1);
	tree = tree->insert(-1);
	tree = tree->insert(4);
	tree = tree->insert(6);
	tree->output();
	system("PAUSE");
	tree->release();
	return 0;
}