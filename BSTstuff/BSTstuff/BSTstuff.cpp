// BSTstuff.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <stack>
#include <string>
using namespace std;

#define MAX_CHARACTER 256

struct BSTNode {
	int data;
	BSTNode *left;
	BSTNode *right;
};


struct BSTree {
	BSTNode *root;
};

//Create a BSTree
void createBSTree(BSTree &tree) {
	tree.root = nullptr;
}

//Allocate a new node
BSTNode* newNode(int data) {

	//Allocate the memory for a BSTNode
	BSTNode* temp = (struct BSTNode*)malloc(sizeof(struct BSTNode));

	//If can not allocate, return null;
	if (!temp) {
		system("cls");
		cout << "Cap phat bo nho that bai !\n";
		cout << "Chuong trinh se ket thuc !\n";
		system("PAUSE");
		return nullptr;
	}

	//Set data
	temp->data = data;
	temp->left = temp->right = nullptr;
	return temp;
}

int insertNewBSTNode(BSTree &tree, int data) {
	
	//If the tree is empty
	if (!tree.root) {
		tree.root = newNode(data);
		if (!tree.root) return 0;
		return 1;
	}

	//If the tree is not empty
	BSTNode *current = tree.root;
	while (1) {
		//If data of the child node < data of the parent node
		if (data < current->data) {
			//Try to insert to the left branch
			if (!current->left) {
				current->left = newNode(data);

				//If can not allocate the memmory, return false
				if (!current->left) return 0;

				//else, return true
				return 1;
			}
			else current = current->left;
		}
	
		//else, try to insert to the right branch
		else {
			if (!current->right) {
				current->right = newNode(data);

				//If can not allocate the memmory, return false
				if (!current->right) return 0;

				//else, return true
				return 1;
			}
			else current = current->right;
		}
	}
}
void releaseBSTree(BSTNode* &node) {
	if (!node) return;
	releaseBSTree(node->left);
	releaseBSTree(node->right);
	free(node);
}

//Input a Tree
bool input(BSTree &tree) {
	createBSTree(tree);
	system("cls");
	int id = 0;
	int data;
	cout << "*****De ket thuc viec nhap, thay hay nhan: Ctrl + X\n\n";
	cout << "Moi thay nhap da ta cua #" << id << " node: ";
	//input
	while (cin >> data) {	

		int check = insertNewBSTNode(tree, data);

		//If can not allocate the memory
		if (check == 0) {

			//Release all the memory which has been allocated
			releaseBSTree(tree.root);
			cin.clear();
			cin.ignore(MAX_CHARACTER, '\n');

			//exit function
			return false;
		}
		
		cin.clear();
		cin.ignore(MAX_CHARACTER, '\n');
		++id;
		cout << "Moi thay nhap data cua #" << id << " node: ";
	}
	cin.clear();
	cin.ignore(MAX_CHARACTER, '\n');
	return true;
}
//Print the tree
void output(BSTNode* node) {
	if (node) {
		output(node->left);
		cout << node->data << " ";
		output(node->right);
	}
}

//Calculate the height of tree
int height(BSTNode* node) {
	if (!node) return 0;
	int leftHeight = height(node->left);
	int rightHeight = height(node->right);
	return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

//Count the leafs
int countLeaf(BSTNode* node) {
	if (!node) return 0;
	if (!node->left && !node->right) return 1;
	
	return countLeaf(node->left) + countLeaf(node->right);
}

//Find the node which has given data
BSTNode* search(BSTree tree, int data) {
	BSTNode* result = tree.root;
	while (result) {
		if (data == result->data) return result;
		else if (data < result->data) result = result->left;
			 else result = result -> right;
	}
	return nullptr;
}

//Find the node which is the parent of target above
BSTNode* searchParent(BSTree& tree, int data) {
	BSTNode* parent = tree.root;
	while (parent) {
		if (data == parent->left->data) {
			parent->left = nullptr;
			return parent;
		}

		if (data == parent->right->data) {
			parent->right = nullptr;
			return parent;
		}
		else if (data < parent->right->data) parent = parent->left;
		else parent = parent->right;
	}
	return nullptr;
}

//Find the left most node, from a center node
BSTNode* leftMostNode(BSTNode* centerNode) {
	if (!centerNode) return nullptr;
	while (centerNode->left) centerNode = centerNode->left;
	return centerNode;
}

//Find the right most node, from a center node
BSTNode *rightMostNode(BSTNode* centerNode) {
	if (!centerNode) return nullptr;
	while (centerNode->right) centerNode = centerNode->right;
	return centerNode;
}

//Release leaf (Node which having 0 child)
void deleteLeaf(BSTree& tree, BSTNode *&leaf) {
	if (!leaf) return;
	if (!leaf->left && !leaf->right) free(leaf);
	else return;
	if (tree.root == leaf) tree.root = nullptr;
	leaf = nullptr;
}

//Release Node which having <= 1 child
void deleteNodeHavingAtMostOneChild(BSTree &tree, BSTNode *&targetNode) {
	if (!targetNode) return;

	//If the node have 2 child, exit function
	if (targetNode->left && targetNode->right) return;
	else {

		//If the child is left
		if (targetNode->left) {
			BSTNode*dummy = targetNode->left;
			targetNode->data = dummy->data;
			targetNode->left = dummy->left;
			targetNode->right = dummy->right;
			free(dummy);
			dummy = nullptr;
			targetNode->left = nullptr;
		}
		else {

			//If the child is right
			if (targetNode->right) {
				BSTNode*dummy = targetNode->right;
				targetNode->data = dummy->data;
				targetNode->left = dummy->left;
				targetNode->right = dummy->right;
				free(dummy);
				dummy = nullptr;
				targetNode->right = nullptr;
			}
			else {

				//If the node have no child, delete like a leaf
				deleteLeaf(tree, targetNode);
			}
		}
	}
}

//Release Node which having <= 2 childs
void deleteNode(BSTree &tree, BSTNode *&targetNode) {
	if (!targetNode) return; 
	if (targetNode->left && targetNode->right) {
		BSTNode*dummy = rightMostNode(targetNode->left);
		targetNode->data = dummy->data;
		deleteNodeHavingAtMostOneChild(tree, dummy);
	}
	else {
		deleteNodeHavingAtMostOneChild(tree, targetNode);
	}
}

void menu_text() {
	cout << "-------------Menu------------\n";
	cout << "1. Nhap du lieu vao cay.\n";
	cout << "2. In ra cac gia tri cua cay\n";
	cout << "3. Tinh chieu cao cua cay\n";
	cout << "4. Dem so node la cua cay\n";
	cout << "5. Xoa mot node bat ki\n";
	cout << "6. Tim dia chi o nho cua node co gia tri can tim\n";
	cout << "-----------------------------\n";
	cout << "0. De thoat khoi chuong trinh\n";
	cout << "-----------------------------\n";
	cout << "Moi thay nhap chuc nang: ";
}

int menu() {
	string selection;
	int select = -1;
	bool isNumber = true;

	menu_text();
	getline(cin, selection);

	for (unsigned int i = 0; i < selection.length(); ++i)
		if (selection[i]<'0' || selection[i]>'9') {
			isNumber = false;
			break;
		}

	if (isNumber) select = stoi(selection);

	
	while (select < 0 || select > 6) {

		isNumber = true;

		system("cls");
		cout << "Thay nhap khong hop le!\n";
		system("pause");
		system("cls");
		menu_text();
		getline(cin, selection);

		
		for (unsigned int i = 0; i < selection.length(); ++i)
			if (selection[i]<'0' || selection[i]>'9') {
				isNumber = false;
				break;
			}

		if (isNumber) select = stoi(selection);
	}

	return select;
}



void selectMenu(BSTree& tree) {
	int select;
	int data;
	BSTNode *target = nullptr;
	do {
		system("cls");
		select = menu();
		system("cls");

		switch (select)
		{
		case 1:
			input(tree);
			break;
		case 2:
			cout << "Cac du lieu trong cay la: ";
			output(tree.root);
			cout << endl;
			system("PAUSE");
			break;
		case 3:
			cout << "Chieu cao cua cay la: " << height(tree.root) << endl;
			system("PAUSE");
			break;
		case 4:
			cout << "So nut la cua cay la: " << countLeaf(tree.root) << endl;
			system("PAUSE");
			break;
		case 5:
			cout << "Moi thay nhap gia tri cua node muon xoa (Luu y: neu co nhieu phan tu bang thi se xoa phan tu dau tien: ";
			cin >> data;
			cin.ignore();
			target = search(tree, data);
			if (target) {
				BSTNode*parent = searchParent(tree, data);
				deleteNode(tree, target);
				cout << "Da xoa xong!\n";
			}
			else {
				cout << "Khong ton tai phan tu can xoa!\n";
			}
			system("PAUSE");
			break;
		case 6:
			cout << "Moi thay nhap gia tri cua node can tim (Luu y: neu co nhieu gia tri giong nhau thi se chi ra node dau tien)\n";
			cout << "Moi thay nhap: ";
			cin >> data;
			cin.ignore();
			target = nullptr;
			target = search(tree, data);
			if (target) {
				cout << "Dia chi o nho cua node can tim la: " << target << endl;
			}
			else {
				cout << "Khong ton tai gia tri can tim\n";
			}
			system("PAUSE");
		case 0:
			releaseBSTree(tree.root);
		}
		
	} while (select != 0);
}

int main()
{
	BSTree tree;
	tree.root = nullptr;
	selectMenu(tree);
    return 0;
}

