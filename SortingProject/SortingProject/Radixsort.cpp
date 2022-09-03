#include "Sort.h"
#include <queue>
#include <cstdlib>
using namespace std;

#define RADIX 10 //0, 1, 2, 3, ...., 9

void radixSort(int *&a, int n, ComparisionFunction compare) {
	int max = a[0], exp = 1;
	int *temp_a = (int*)malloc(n * sizeof(int));

	//If can not allocate, end the fucntion
	if (!temp_a) return;


	//Find the maximum value of the array
	for (int i = 0; i < n; ++i) if (max < a[i]) max = a[i];

	while (max / exp > 0) {

		//set all the frequency of digit 0, 1, 2, ..., 9 to 0
		int freq[RADIX] = { 0 };

		//Counting sort
		for (int i = 0; i < n; ++i) ++freq[a[i] / exp % RADIX];
		for (int i = 1; i < RADIX; ++i) freq[i] += freq[i - 1];

		//Ascending counting sort
		if (compare(2, 1)) {
			for (int i = n - 1; i >= 0; --i) temp_a[--freq[a[i] / exp % RADIX]] = a[i];
			for (int i = 0; i < n; ++i) a[i] = temp_a[i];
		}
		else {

			//Descending counting sort
			for (int i = 0; i < n; ++i) temp_a[--freq[a[i] / exp % RADIX]] = a[i];
			for (int i = 0; i < n; ++i) a[i] = temp_a[n - i - 1];
		}
		//tend to the next digit
		exp *= 10;
	}


	//release the memmory
	release(temp_a);
}

