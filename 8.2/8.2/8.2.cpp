#include <iostream>
#include <malloc.h>
using namespace std;


struct SNode {
	int data;
	SNode *next;
};

struct SList {
	SNode *head;
};


void createDList(SList &a) {
	a.head = nullptr;
}

bool emptyCheck(SList a) {
	return (!a.head);
}

SNode *newNode(int dat) {
	SNode *temp = nullptr;
	temp = (SNode*)malloc(sizeof(SNode));
	if (!temp) {
		cout << "Cap phat that bai!\n";
		system("pause");
		return nullptr;
	}
	temp->data = dat;
	temp->next = nullptr;
	return temp;
}

SNode *inputOneSNode() {
	int dat;
	cout << "Moi thay nhap gia tri cua phan tu can them: ";
	cin >> dat;
	return newNode(dat);
}

void inputSList(SList &a) {
	int dat, quantity = 0;
	createDList(a);
	SNode *currentNode = nullptr;
	SNode *pastNode = nullptr;
	cout << "Moi thay nhap cac gia tri trong danh sach lien ket don (VD: nhap cac gia tri: 10 8 6 4 2 0 (Thay nen nhap giam dan de de xem ket qua y thu 3))\n";
	cout << "De ngung nhap, moi thay nhan: Ctrl + X\n";
	cout << "Moi thay nhap:\n";
	while (cin >> dat) {
		++quantity;
		currentNode = newNode(dat);
		if (quantity == 1) {
			a.head = currentNode;
			pastNode = currentNode;
		}
		else {
			pastNode->next = currentNode;
			pastNode = currentNode;
		}
	}
	cin.clear();
	cin.ignore();
}

int countElement(SList a) {
	int result = 0;
	if (emptyCheck(a)) return 0;
	for (SNode *ptr = a.head; ptr; ptr = ptr->next) {
		result++;
	}
	return result;
}

void reverseSList(SList &a) {
	if (emptyCheck(a)) return;
	SNode *prev = nullptr;
	SNode *temp = nullptr;
	SNode *current = a.head;
	while (current != nullptr) {
		temp = current->next;
		current->next = prev;
		prev = current;
		current = temp;
	}
	a.head = prev;
}

void removeSListHead(SList &a) {
	if (emptyCheck(a)) return;
	SNode *temp = a.head;
	if (!temp->next) {
		a.head = nullptr;
		free(temp);
	}
	else {
		a.head = temp->next;
		free(temp);
	}
}

void addSNodeHead(SList &a, SNode *object) {
	if (emptyCheck(a)) {
		a.head = object;
	}
	else {
		SNode *temp = a.head;
		a.head = object;
		object->next = temp;
	}
}

void addSNodeKeepPosition(SList &a, SNode *object) {
	if (emptyCheck(a)) {
		addSNodeHead(a, object);
		return;
	}
	SNode *prePos = nullptr;
	for (SNode *ptr = a.head; ptr && (ptr->data < object->data); ptr = ptr->next) {
		prePos = ptr;
	}
	if (!prePos) {
		addSNodeHead(a, object);
		return;
	}
	object->next = prePos->next;
	prePos->next = object;
}

void removeAllSList(SList &a) {
	while (!emptyCheck(a)) {
		removeSListHead(a);
	}
}

void output(SList a) {
	for (SNode *ptr = a.head; ptr; ptr = ptr->next) {
		cout << ptr->data << " ";
	}
	cout << endl;
}

int main() {
	SList a;
	cout << ("Luu y: input thay nhap se duoc dung cho tat ca cac y trong bai 8.2 mot cach lien tiep\n\n");
	inputSList(a);
	cout << "- So phan tu cua danh sach lien ket don la: " << countElement(a) << endl;
	reverseSList(a);
	cout << "- Sau khi dao nguoc, cac du lieu cua danh sach tro thanh: ";
	output(a);
	cout << "- Tiep theo la them phan tu (va giu nguyen thu tu)\n";
	SNode *input = inputOneSNode();
	addSNodeKeepPosition(a, input);
	cout << "\t+ Sau khi them vao, danh sach tro thanh: ";
	output(a);
	cout << "- Truoc khi ket thuc chuong trinh se thuc hien thu hoi bo nho!\n";
	removeAllSList(a);
	return 0;
}