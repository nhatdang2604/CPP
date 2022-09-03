#include "Sort.h"
#include <cstdlib>
#include <string.h>
using namespace std;

void countingSort(int *&a, int n, ComparisionFunction compare) {
	int max = a[0];

	//find max
	for (int i = 1; i < n; ++i) {
		if (max < a[i]) max = a[i];
	}

	//allocate the memmory
	int *freq = (int *)malloc((max + 1) * sizeof(int));

	//if can not allocate the memmory, exit the function
	if (!freq) return;
	
	memset(freq, 0, (max + 1) * sizeof(int));

	//calculate the frequency of each element
	for (int i = 0; i < n; ++i) ++freq[a[i]];

	if (compare(2, 1)) {

		//Ascending sort
		int k = 0;
		for (int i = 0; i <= max; ++i) {
			while (freq[i] > 0) {
				a[k] = i;
				--freq[i];
				++k;
			}
		}
	}
	else {

		//Descending sort
		int k = n - 1;
		for (int i = 0; i <= max; ++i) {
			while (freq[i] > 0) {
				a[k] = i;
				--freq[i];
				--k;
			}
		}
	}
	//release the memmory
	release(freq);
}