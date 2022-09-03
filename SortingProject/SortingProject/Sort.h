#pragma once

#ifndef  _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef  MAX_CHARACTERS
#define MAX_CHARACTERS 256
#endif

#ifndef  NUMBER_OF_SORTS
#define NUMBER_OF_SORTS 9
#endif

//Input or Random Generator Test
bool input(int *&a, int &n);
bool randomGeneratorTest(int *&a, int &n);

//Comparision pointer
typedef bool(*ComparisionFunction)(int a, int b);

//Comparision function (Sort type)
bool ascending(int left, int right);
bool descending(int left, int right);

//Swap function
void swap(int &a, int &b);

//Sort algorithm
void selectionSort(int *&a, int n, ComparisionFunction compare);
void insertionSort(int *&a, int n, ComparisionFunction compare);
void bubbleSort(int *&a, int n, ComparisionFunction compare);
void shellSort_KnuthIncr(int *&a, int n, ComparisionFunction compare);
void heapSort(int *&a, int n, ComparisionFunction compare);
void mergeSort(int *&a, int n, ComparisionFunction compare);
void quickSort(int *&a, int n, ComparisionFunction compare);
void radixSort(int *&a, int n, ComparisionFunction compare);
void countingSort(int *&a, int n, ComparisionFunction compare);

//Sort algortihtm pointer
typedef void(*sortAlgorithm)(int *&arr, int n, ComparisionFunction compare);

//Case (For random test)
void random_case(sortAlgorithm sorting, int *&a, int n);
void foward_case(sortAlgorithm sorting, int *a, int n);
void reverse_case(sortAlgorithm sorting, int *a, int n);

//Time calculate
double timeCalculating(sortAlgorithm sorting, ComparisionFunction compare, int *a, int n);
void timeCalculator(char sortName[], sortAlgorithm sorting, int *a, int n);;

//Output and Release
void output(int *a, int n);
void release(int *&a);

//Heapsort stuffs
void heapifyMaxHeap(int *&a, int n, int i, ComparisionFunction compare);
void buildMaxHeap(int *&a, int n, ComparisionFunction compare);

//Mergesort stuffs
void split(int *source, int *&left, int*&right, int leftLength, int rightLength);
void merge(int *&source, int *&left, int *&right, int leftLength, int rightLength, ComparisionFunction compare);

//Quicksort stuffs
void _quickSort(int *&a, int left, int right, ComparisionFunction compare);

//Singularity Sort Call
class Sort {
public:

private:
	Sort();
	~Sort();

};