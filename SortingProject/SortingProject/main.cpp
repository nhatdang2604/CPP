#include "Sort.h"
#include "stdio.h"
#include <stdlib.h>
#include <string.h>
using namespace std;


void Main_process() {
	int *arr;
	int n;
	char sortName[NUMBER_OF_SORTS][MAX_CHARACTERS] = { "SELECTION SORT",
		"INSERTION SORT", "BUBBLE SORT", "SHELL SORT (USING KNUTH'S INCREMENTS)", "HEAP SORT",
		"MERGE SORT", "QUICK SORT (RANDOMIZED)", "RADIX SORT", "COUNTING SORT" };

	//bool inputCheck = input(arr, n);
	bool inputCheck = randomGeneratorTest(arr, n);

	//If can not allocate the memory, end the program
	if (!inputCheck) return;

	//Sorting
	timeCalculator(sortName[0], selectionSort, arr, n);
	timeCalculator(sortName[1], insertionSort, arr, n);
	timeCalculator(sortName[2], bubbleSort, arr, n);
	timeCalculator(sortName[3], shellSort_KnuthIncr, arr, n);
	timeCalculator(sortName[4], heapSort, arr, n);
	timeCalculator(sortName[5], mergeSort, arr, n);
	timeCalculator(sortName[6], quickSort, arr, n);
	timeCalculator(sortName[7], radixSort, arr, n);
	timeCalculator(sortName[8], countingSort, arr, n);

	//Release memory
	release(arr);
}

int main() {
	Main_process();
	system("PAUSE");
	return 0;
}