#include "Sort.h"
#include <malloc.h>

void split(int *source, int *&left, int*&right, int leftLength, int rightLength) {
	for (int i = 0; i < leftLength; ++i) left[i] = source[i];
	for (int i = 0; i < rightLength; ++i) right[i] = source[leftLength + i];
}

void merge(int *&source, int *&left, int *&right, int leftLength, int rightLength, ComparisionFunction compare) {
	int leftIndex = 0;
	int rightIndex = 0;
	int sourceIndex = 0;

	//when left[] or right[] are not empty
	while (leftIndex < leftLength || rightIndex < rightLength) {

		//when both left[] and right[] are not empty
		if (leftIndex < leftLength && rightIndex < rightLength) {
			if (compare(left[leftIndex], right[rightIndex])) {
				source[sourceIndex] = right[rightIndex];
				++rightIndex;
			}
			else {
				source[sourceIndex] = left[leftIndex];
				++leftIndex;
			}
		}
		else
		{
			//when right[] is empty, left[] is not empty
			if (rightIndex == rightLength) {
				source[sourceIndex] = left[leftIndex];
				++leftIndex;
			}
			else {

				//when left[] is empty, right[] is not empty
				if (leftIndex == leftLength) {
					source[sourceIndex] = right[rightIndex];
					++rightIndex;
				}

			}
		}
		++sourceIndex;
	}
}

void mergeSort(int *&a, int n, ComparisionFunction compare) {
	if (n <= 1) return;
	int leftLength = n / 2;
	int rightLength = n - leftLength;
	int *left = (int*)malloc(leftLength * sizeof(int));
	int *right= (int*)malloc(rightLength * sizeof(int));

	
	split(a, left, right, leftLength, rightLength);

	mergeSort(left, leftLength, compare);
	mergeSort(right, rightLength, compare);

	merge(a, left, right, leftLength, rightLength, compare);

	release(left);
	release(right);
}