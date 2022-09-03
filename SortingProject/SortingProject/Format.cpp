#include "Sort.h"
#include <Windows.h>
#include <time.h>
#include <iostream>

using namespace std;

//Input from a file input.txt
bool input(int *&a, int &n) {
	FILE *f = fopen("input.txt", "r");

	//If can not read the file, end the program
	if (!f) return false;

	//read the number of elements in the array
	fscanf(f, "%d", &n);
	a = (int *)malloc(n * sizeof(int));

	//if can not allocate, end the program
	if (!a) return false;

	//else, read the array
	for (int i = 0; i < n; ++i) {
		fscanf(f, "%d", &a[i]);
	}
	fclose(f);
	return true;
}

//If you don't input from a file, you can generate random test
bool randomGeneratorTest(int *&a, int &n) {
	printf("Please input the number of random element: ");
	scanf("%d", &n);

	a = (int *)malloc(n * sizeof(int));

	//if can not allocate, end the program
	if (!a) return false;

	//else, generate the array
	srand((unsigned int)time(0));
	for (int i = 0; i < n; ++i) {
		a[i] = rand();
	}

	return true;
}

//Time calculate for each of the sort algorithm
double timeCalculating(sortAlgorithm sorting, ComparisionFunction compare, int *a, int n) {
	clock_t start, end;
	double cpu_time_used;

	//start clock
	start = clock();

	//Start sorting
	sorting(a, n, compare);

	//end clock
	end = clock();

	//calculate the used time
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	return cpu_time_used;
}

//All case (For random test)
void random_case(sortAlgorithm sorting, int *&a, int n) {
	cout << "Random case: " << timeCalculating(sorting, ascending, a, n) << "s" << endl;
}
void foward_case(sortAlgorithm sorting, int *a, int n) {
	cout << "Foward case: " << timeCalculating(sorting, ascending, a, n) << "s" << endl;
}
void reverse_case(sortAlgorithm sorting, int *a, int n) {
	cout << "Reverse case: " << timeCalculating(sorting, descending, a, n) << "s" << endl;
}

//Calculating all case (For random test)
void timeCalculator(char sortName[], sortAlgorithm sorting, int *a, int n) {
	cout << endl << sortName << endl << endl;
	random_case(sorting, a, n);
	foward_case(sorting, a, n);
	reverse_case(sorting, a, n);
	cout << "********************" << endl;
}

//Release the memmory if it have been allocated
void release(int *&a) {

	//if have not allocated memmory, exit the function
	if (!a) return;

	//else, release the memmory
	free(a);
}

//Output the result;
void output(int *a, int n) {
	for (int i = 0; i < n; ++i) {
		printf("%d ", a[i]);
	}
	printf("\n");
}


