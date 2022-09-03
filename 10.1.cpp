#include <iostream>
#include <malloc.h>
using namespace std;

struct SNode {
	int data;
	SNode* next;
};

struct SList {
	SNode *head;
	SNode *tail;
};

void createSList(SList &list) {
	list.head = list.tail = nullptr;
}

bool isEmpty(SList list) {
	return (!list.head);
}

SNode* getNode(int dat) {
	SNode* temp = (SNode*)malloc(sizeof(SNode));
	if (!temp) {
		system("cls");
		cout << "Het bo nho!\n";
		system("pause");
		return nullptr;
	}
	temp->data = dat;
	temp->next = nullptr;
	return temp;
}

bool addLast(SList& list, int dat) {
	SNode* p = getNode(dat);
	if (!p) return false;
	if (isEmpty(list)) {
		list.head = list.tail = p;
	}
	else {
		list.tail->next = p;
		list.tail = p;
	}
	return true;
}

void inputInstruction() {
	cout << "Moi thay nhap cac gia tri cua tung phan tu!\n\n";
	cout << "De ket thuc, moi thay nhap Ctrl + X\n\n";
}

void input(SList&list, int &size) {
	system("cls");
	inputInstruction();
	int dat;
	int count = 0;
	createSList(list);
	cout << "Moi thay nhap gia tri thu " << count << " : ";
	while (cin >> dat) {
		system("cls");
		++count;
		if (!addLast(list, dat)) {
			system("cls");
			cout << "Het dung luong bo nho!\n\n";
			cout << "Se thoat khoi ham ngay lap tuc! \n\n";
			system("pause");
			return;
		}
		inputInstruction();
		cout << "Moi thay nhap gia tri thu " << count << " : ";
	}
	size = count;
	cin.clear();
	cin.ignore();
}

void releaseMemmory(SList& list) {
	SNode* temp;
	while (!isEmpty(list)) {
		temp = list.head;
		list.head = list.head->next;
		free(temp);
	}
	list.tail = nullptr;
}

void printList(SList list) {
	for (SNode* p = list.head; p; p = p->next) {
		cout << p->data << " ";
	}
	cout << endl << endl;
}

//----------------------------------------------------------------

SNode *findIthNode(SList list, int i) {
	int count = 0;
	for (SNode *j = list.head; j; j = j->next) {
		if (count == i) return j;
		++count;
	}
	return nullptr;
}

void createMiniSlist(SList source, SNode *from, SNode *to, SList &des) {
	createSList(des);
	SNode *pivot_source = from;
	des.head = getNode(from->data);
	SNode *pivot_des = des.head;
	if (from != to) {
		do {
			pivot_source = pivot_source->next;
			pivot_des->next = getNode(pivot_source->data);
			pivot_des = pivot_des->next;
		} while (pivot_source != to);
	}
	des.tail = pivot_des;
}

void mergeList(SList &a, SList &b, SList &c) {
	SNode *pivot_a = a.head, *pivot_b = b.head, *pivot_c = c.head;
	while (pivot_a || pivot_b) {
		if (!pivot_a && pivot_b){
			pivot_c->data = pivot_b->data;
			pivot_b = pivot_b->next;
		}
		if (pivot_a && !pivot_b) {
			pivot_c->data = pivot_a->data;
			pivot_a = pivot_a->next;
		}
		if (pivot_a && pivot_b) {
			if (pivot_a->data > pivot_b->data) {
				pivot_c->data = pivot_b->data;
				pivot_b = pivot_b->next;
			}
			else {
				pivot_c->data = pivot_a->data;
				pivot_a = pivot_a->next;
			}
		}
		pivot_c = pivot_c->next;
	}
}

void mergeSort(SList &list, int size) {
	if (size == 1) return;
	int size_a = size / 2;
	int size_b = size - size_a;
	SList a, b;
	SNode *temp = findIthNode(list, size_a - 1);
	createMiniSlist(list, list.head, temp, a);
	createMiniSlist(list, temp->next, list.tail, b);
	mergeSort(a, size_a);
	mergeSort(b, size_b);
	mergeList(a, b, list);
	releaseMemmory(a);
	releaseMemmory(b);
}

void output(SList &list, int size) {
	system("cls");
	cout << "Cac gia tri cua danh sach luc dau la: \n\n";
	printList(list);
	cout << "Cac gia tri cua danh sach sau khi sap xep la: \n\n";
	mergeSort(list, size);
	printList(list);
}

int main() {
	SList list;
	int size = 0;
	input(list, size);
	output(list, size);
	releaseMemmory(list);
	return 0;
}