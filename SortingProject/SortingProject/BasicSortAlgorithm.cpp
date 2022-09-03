#include"Sort.h"
#include<iostream>

//Comparision function (Sort type)
bool ascending(int left, int right) {
	return left > right;
}
bool descending(int left, int right) {
	return left < right;
}

//Swap function
void swap(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}

//Sort Algorithm
void selectionSort(int *&a, int n, ComparisionFunction compare) {
	int min;
	for (int i = 0; i < n - 1; ++i) {
		min = i;
		for (int j = i + 1; j < n; ++j) {
			if (compare(a[min], a[j])) {
				min = j;
			}
		}
		if (compare(a[i], a[min])) swap(a[min], a[i]);
	}
}
void insertionSort(int *&a, int n, ComparisionFunction compare) {
	int save, j;
	for (int i = 1; i < n; ++i) {
		save = a[i];
		for (j = i - 1; j >= 0; --j) {
			if (compare(a[j], save)) a[j + 1] = a[j];
			else break;
		}
		a[j + 1] = save;
	}
}
void bubbleSort(int *&a, int n, ComparisionFunction compare) {
	for (int i = 0; i < n - 1; ++i) {
		for (int j = n - 1; j > i; --j) {
			if (compare(a[j-1], a[j])) swap(a[j], a[j - 1]);
		}
	}
}
void shellSort_KnuthIncr(int *&a, int n, ComparisionFunction compare) {
	// interval[0]=1
	int interval = 1;

	//Tinh toan khoang interval max
	while (interval < n / 3) {
		interval = 3 * interval + 1;
	}

	while (interval > 1) {
		for (int i = 0; i < n - interval; ++i) {
			if (compare(a[i], a[i + interval])) {
				swap(a[i], a[i + interval]);
			}
		}
		interval = (interval - 1) / 3;
	}

	//Khi interval = 1, thuc hien insertionSort (Vi insertionSort rat nhanh khi sap xep mang gan hoan thanh)
	insertionSort(a, n, compare);
}
