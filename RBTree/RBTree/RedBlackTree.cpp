#include "RedBlackTree.h"



RBNode::RBNode(const int& dataValue, const color& colorValue) {
	this->data = dataValue;
	this->colour = colorValue;
}

RBNode::~RBNode() {}

/*Height calculation implementation*/
int RBNode::_height() {
	if (!this) return 1;
	if (this->heightData == 0) {
		this->heightData = MAX(this->left->_height(), this->right->_height()) + 1;
	}
	return this->heightData;
}

/*Height calculation API*/
int RBNode::height() {
	return this->_height();
}


bool RBNode::isRed() {
	if (!this) return BLACK;
	return this->colour;
}

void RBNode::flipColor() {
	if (!this) return;
	this->colour = !this->colour;
	if (this->left) this->left->colour = !this->left->colour;
	if (this->right) this->right->colour = !this->right->colour;
}

/*Return RBNode* which currently the main node */
/*Warning: The parent node's left/right hasn't been configed*/
RBNode* RBNode::leftRotation() {
	RBNode* newMain = this->right;
	RBNode* newLeft = this;
	RBNode* newLeftRight = nullptr;
	if (this->right) {
		newLeftRight = this->right->left;
	}
	newMain->left = newLeft;
	newLeft->right = newLeftRight;
	return newMain;
}

/*Return RBNode* which currently the main node */
/*Warning: The parent node's left/right hasn't been configed*/
RBNode* RBNode::rightRotation() {
	RBNode* newMain = this->left;
	RBNode* newRight = this;
	RBNode* newRightLeft = nullptr;
	if (this->left) {
		newRightLeft = this->left->right;
	}
	newMain->right = newRight;
	newRight->left = newRightLeft;
	return newMain;
}

/*Return the current root*/
RBNode* RBNode::_insert(const int& data) {
	if (!this) return new RBNode(data, RED);

	//Traversal
	if (data < this->data) this->left = this->left->_insert(data);
	else this->right = this->right->_insert(data);

	//Rebalanced
	if (this->right->isRed() && !this->left->isRed()) {
		RBNode* current = this->leftRotation();
		current->colour = current->left->colour;
		current->left->colour = RED;
		return current;
	}
	if (this->left->isRed() && this->left->left->isRed()) {
		RBNode* current = this->rightRotation();
		current->colour = BLACK;
		current->left->colour = current->right->colour = RED;
		return current;
	}
	if (this->left->isRed() && this->right->isRed()) flipColor();
	return this;
}

/*API: Return the current root*/
RBNode* RBNode::insert(const int& data) {
	return _insert(data);
}

void RBNode::_release() {
	if (this->left)  this->left->_release();
	if (this->right) this->right->_release();
	delete this;
}

void RBNode::release() {
	_release();
}

//print the data of a node
void RBNode::printNode(RBNode* node, int tabSize) {
	if (node) 
		cout << "(" << node->data << ", " << node->colour<<")";
	else 
		cout << " ";

	for (int i = 0; i < tabSize; ++i) cout << " ";
}

//print the data of tree, in tree form (by using BFS)
void RBNode::_output(RBNode* root) {
	queue<RBNode*> traversalNode;
	int tabSize = int(pow(2, root->_height()));	//tab size to print
	int currentHeight = 1;						//use to calculate the current level in the tree
	int index = -1;								//use to get the current index of a node

												//Push the root of the tree into the queue
	traversalNode.push(root);

	//Print the left-margin-tab for the root
	for (int i = 0; i < tabSize - 1; ++i) cout << " ";

	while (!traversalNode.empty()) {
		++index;

		//When reach new level of the tree => endl + print left-margin-tab + config the tabSize + update the new height
		if (index == 2 * currentHeight - 1) {
			currentHeight *= 2;
			tabSize /= 2;
			cout << endl;
			for (int i = 0; i < tabSize - 1; ++i) cout << " ";
		}

		//Get the current node in the queue
		RBNode* current = traversalNode.front();
		traversalNode.pop();

		//Print the current node
		printNode(current, 2 * tabSize - 1);

		//If the current node is a null-node => continue
		if (!current) continue;

		//push the 2 children of the current node into the queue (even if the child node is a null-node)
		traversalNode.push(current->left);
		traversalNode.push(current->right);
	}
	cout << endl;
}

void RBNode::output() {
	_output(this);
}