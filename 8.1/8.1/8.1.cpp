#include <iostream>
#include <malloc.h>
using namespace std;


struct DNode {
	int data;
	DNode *next, *previous;
};

struct DList {
	DNode *head, *tail;
};

void output(DList a);

void createDList(DList &a) {
	a.head = a.tail = nullptr;
}

bool emptyCheck(DList a) {
	return (!a.head);
}

DNode *newNode(int dat) {
	DNode *temp = nullptr;
	temp = (DNode*)malloc(sizeof(DNode));
	if (!temp) {
		cout << "Cap phat that bai!\n";
		system("pause");
		return nullptr;
	}
	temp->data = dat;
	temp->next = nullptr;
	temp->previous = nullptr;
	return temp;
}

DNode *inputOneDNode() {
	int dat;
	cout << "Moi thay nhap gia tri cua phan tu can them: ";
	cin >> dat;
	return newNode(dat);
}

void inputDList(DList &a) {
	int dat, quantity = 0;
	createDList(a);
	DNode *currentNode = nullptr;
	DNode *pastNode = nullptr;
	cout << "Moi thay nhap cac gia tri trong danh sach lien ket kep (VD: nhap cac gia tri: 2 4 6 8 10)\n";
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
			currentNode->previous = pastNode;
			pastNode->next = currentNode;
			pastNode = currentNode;
		}
	}
	a.tail = currentNode;
	cin.clear();
	cin.ignore();
}

DNode *findIthDNode(DList a, int i) {
	int count = 0;
	for (DNode *j = a.head; j; j = j->next) {
		if (count == i) return j;
		++count;
	}
	return nullptr;
}

DNode *findDNodeHavingX(DList a, int x) {
	for (DNode *j = a.head; j; j = j->next) {
		if (j->data == x) {
			return j;
		}
	}
	return nullptr;
}

DNode *findDNodeTail(DList a) {
	return a.tail;
}

void addDNodeHead(DList &a, DNode *object) {
	if (emptyCheck(a)) {
		a.head = a.tail = object;
	}
	else {
		DNode *temp = a.head;
		a.head = object;

		//When we create a DNode, we have already set its prev and next as nullptr
		//object->previous = nullptr;

		object->next = temp;
		temp->previous = object;
	}
}

void addDNodeTail(DList &a, DNode *object) {
	if (emptyCheck(a)) {
		a.head = a.tail = object;
	}
	else {
		DNode *Tail = findDNodeTail(a);
		a.tail = object;

		//When we create a DNode, we have already set its prev and next as nullptr
		//object->next = nullptr;

		object->previous = Tail;
		Tail->next = object;
	}
}

void addDNodeAfterI(DList &a, DNode *object, int i) {
	DNode *sample = findIthDNode(a, i);
	if (!sample) {
		cout << "Chen that bai!\n";
		system("pause");
		free(object);
		return;
	}
	object->previous = sample;
	object->next = sample->next;
	if (a.tail == sample) a.tail = object;
	if (sample->next) {
		sample->next->previous = object;
		sample->next = object;
	}
	output(a);
}

void addDNodeKeepPosition(DList &a, DNode *object) {
	if (emptyCheck(a)) {
		addDNodeHead(a, object);
		return;
	}
	DNode *prePos = nullptr;
	for (DNode *ptr = a.head; ptr && (ptr->data < object->data); ptr = ptr->next) {
		prePos = ptr;
	}
	if (!prePos) {
		addDNodeHead(a, object);
		return;
	}
	object->previous = prePos;
	object->next = prePos->next;
	if (prePos->next) prePos->next->previous = object;
	prePos->next = object;
	if (a.tail == prePos) a.tail = object;
}

void removeDListHead(DList &a) {
	if (emptyCheck(a)) return;
	DNode *temp = a.head;
	if (!temp->next) {
		a.head = a.tail = nullptr;
		free(temp);
	}
	else {
		a.head = temp->next;
		temp->next->previous = nullptr;
		free(temp);
	}
}

void removeDlistTail(DList &a) {
	if (emptyCheck(a)) return;
	DNode *temp = a.tail;
	if (!temp->previous) {
		a.head = a.tail = nullptr;
		free(temp);
	}
	else {
		a.tail = temp->previous;
		temp->previous->next = nullptr;
		free(temp);
	}
}

void removeDNodeAfterI(DList &a, int i) {
	DNode *object = findIthDNode(a, i + 1);
	if (!object) {
		cout << "Khong ton tai phan tu thu i!\n";
		return;
	}
	DNode *temp = object;
	if (temp->previous) object->previous->next = object->next;
	if (temp->next) object->next->previous = object->previous;
	if (a.head == temp) a.head = temp->next;
	if (a.tail == temp) a.tail = temp->previous;
	free(object);
	output(a);
}

void removeDNodeHavingX(DList &a, int x) {
	DNode *object = findDNodeHavingX(a, x);
	if (!object) {
		cout << "Khong co phan tu co du lieu " << x << endl;
		return;
	}
	DNode *temp = object;
	if (temp->previous) object->previous->next = object->next;
	if (temp->next) object->next->previous = object->previous;
	if (a.head == temp) a.head = temp->next;
	if (a.tail == temp) a.tail = temp->previous;
	free(object);
	output(a);
}

void removeAllDList(DList &a) {
	while (!emptyCheck(a)) {
		removeDListHead(a);
	}
}

void output(DList a) {
	cout << "Du lieu cua danh sach luc nay la: ";
	for (DNode *ptr = a.head; ptr; ptr = ptr->next) {
		cout << ptr->data << " ";
	}
	cout << endl;
}

int main() {
	DList a;
	int i, x;
	cout << ("Luu y: input thay nhap se duoc dung cho tat ca cac y trong bai 8.1 mot cach lien tiep\n\n");
	inputDList(a);
	(emptyCheck(a)) ? cout << "- Danh sach rong!\n" : cout << "- Danh sach khong rong!\n";
	cout << "Moi thay nhap phan tu thu i muon tim: ";
	cin >> i;
	DNode *result = findIthDNode(a, i);
	if (result) {
		cout << "Phan tu thu " << i << " co du lieu la: " << result->data << endl;
	}
	else {
		cout << "Khong tim duoc!\n";
	}
	cout << "Moi thay nhap du lieu x can tim: ";
	cin >> x;
	result = findDNodeHavingX(a, x);
	if (result) {
		cout << "Phan tu co du lieu " << x << " co dia chi la: " << result << endl;
	}
	else {
		cout << "Khong tim duoc!\n";
	}
	result = findDNodeTail(a);
	if (result) {
		cout << "Phan tu cuoi day co du lieu la: " << result->data << endl;
	}
	else {
		cout << "Khong ton tai phan tu cuoi day! \n";
	}
	cout << "- Day la sau khi them vao dau danh sach \n";
	DNode *addElement = inputOneDNode();
	addDNodeHead(a, addElement);
	output(a);
	cout << "- Day la sau khi them vao cuoi danh sach \n";
	addElement = inputOneDNode();
	addDNodeTail(a, addElement);
	output(a);
	cout << "- Day la sau khi them vao sau phan tu thu i trong danh sach \n";
	addElement = inputOneDNode();
	cout << "Moi thay nhap i: ";
	cin >> i;
	addDNodeAfterI(a, addElement, i);
	cout << "- Day la sau khi them phan tu vao va giu thu tu\n";
	addElement = inputOneDNode();
	addDNodeKeepPosition(a, addElement);
	output(a);
	cout << "- Day la sau khi xoa dau danh sach\n";
	removeDListHead(a);
	output(a);
	cout << "- Day la sau khi xoa cuoi danh sach\n";
	removeDlistTail(a);
	output(a);
	cout << "- Day la sau khi xoa phan tu sau phan tu thu i\n";
	cout << "Moi thay nhap i: ";
	cin >> i;
	removeDNodeAfterI(a, i);
	cout << "- Day la sau khi xoa phan tu co du lieu x\n";
	cout << "Moi thay nhap x: ";
	cin >> x;
	removeDNodeHavingX(a, x);
	cout << " Truoc khi ket thuc chuong trinh se thuc hien xoa toan bo cac phan tu!\n";
	removeAllDList(a);
	return 0;
}