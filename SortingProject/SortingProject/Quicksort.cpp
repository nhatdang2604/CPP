#include"Sort.h"
#include<iostream>


void _quickSort(int *&a, int left, int right, ComparisionFunction compare) {
	int i = left, j = right;
	int pivot = a[left + rand() % (right - left)];
	while (i <= j) {
		while (compare(pivot, a[i])) ++i;
		while (compare(a[j], pivot)) --j;

		if (i <= j) {
			if (i < j)swap(a[i], a[j]);
			++i;
			--j;
		}
	}
	if (left < j) _quickSort(a, left, j, compare);
	if (i < right) _quickSort(a, i, right, compare);
}

void quickSort(int *&a, int n, ComparisionFunction compare) {
	_quickSort(a, 0, n - 1, compare);
}