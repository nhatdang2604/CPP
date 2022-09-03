#include "Sort.h"

void heapifyMaxHeap(int *&a, int n, int i, ComparisionFunction compare) {

	// save the a[i] value for the last
	int saved = a[i];

	// while a[i] is not a leaf
 	while (i <= n / 2 - 1) {

		//a[child] = the left child node of a[i]
		int child = 2 * i + 1;

		//if a[child] is not the right most leaf of the tree
		if (child < n - 1) {

			//if the right child node is better than the left child node, we would use the right child node instead
			if (!compare(a[child], a[child + 1])) {
				++child;
			}
		}

		//if there is no better position for saved, break the loop
		if (compare(saved, a[child])) break;

		//a[i] = the best possible node of 2 of its child
		a[i] = a[child];

		//Turn into the child node we choose
		i = child;
	}

	//After the loop, a[i] is the best position for saved
	a[i] = saved;
}

//Build a complete Max Heap
void buildMaxHeap(int *&a, int n, ComparisionFunction compare) {

	//From the nodes which are not the leaves, downto the root
	for (int i = n / 2 - 1; i >= 0; --i) {
		heapifyMaxHeap(a, n, i, compare);
	}
}

void heapSort(int *&a, int n, ComparisionFunction compare) {

	//Firstly, build a complete Max Heap
	buildMaxHeap(a, n, compare);

	for (int i = 1; i < n; ++i) {

		//Swap the first and the last nodes, because the first nodes = the maximum of a[0..n-i] array
		swap(a[0], a[n - i]);

		/*Now, we don't care about the last node, because after swaping, it's already the maximum of the array, 
	we will heapify the a[0..n-2] arr and so on, until a[0..0], and continue swaping*/
		heapifyMaxHeap(a, n - i, 0, compare);
	}
}

