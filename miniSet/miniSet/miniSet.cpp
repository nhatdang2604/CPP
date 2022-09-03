// miniSet.cpp : Defines the entry point for the console application.
//

#include <iostream>
using namespace std;

void input(int s[], int &n) {
	cout << "Please input the number of the set: ";
	cin >> n;
	cout << "Please input each element of the set: ";
	for (int i = 0; i < n; i++) {
		cin >> s[i];
	}
	cout << "All the set which belong to the set that you input is: " << endl;
}

void swap(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}

void sortAscending(int s[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (s[i] > s[j]) {
				swap(s[i], s[j]);
			}
		}
	}
}

void setup(bool flag[], int n) {
	for (int i = 0; i < n; i++) {
		flag[i] = true;
	}
}

void output(int result[], int k, int &counting) {
	counting++;
	cout << counting << ")\t" << "S = { ";
	if (k > 0) {
		cout << result[0];
	}
	for (int i = 1; i < k; i++) {
		cout << " ; " << result[i];
	}
	cout << " }" << endl;
}

void miniProcess(int s[], int n, int i, int k, bool flag[], int result[], int &counting) {
	for (int j = 0; j < n; j++) {
		if ((flag[j] == true) && (j<=n-k+i)) {
			if ((i == 0) || ((i >= 1)&&(s[j]>result[i-1]))) {
				result[i] = s[j];
				if (i == k - 1) {
					output(result, k, counting);
				}
				else {
					flag[j] = false;
					miniProcess(s, n, i + 1, k, flag, result, counting);
					flag[j] = true;
				}
			}
		}
	}
}

void coreProcess(int s[], int n, bool flag[], int result[], int &counting) {
	sortAscending(s, n);
	cout << "1)\tS = {   }" << endl;
	for (int k = 0; k <= n; k++) {
		setup(flag, n); 
		for (int i = 0; i <= k; i++) {
			result[i] = s[0] - 1;
		}
		miniProcess(s, n, 0, k, flag, result, counting);
	}
}

int main()
{
	int s[100], result[100], n = 0, counting = 1;
	bool flag[100];
	input(s, n);
	coreProcess(s, n, flag, result, counting);
	return 0;
}

