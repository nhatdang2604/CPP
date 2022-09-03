#include <iostream>
#include <stdio.h>
using namespace std;

void input(char n[], int &k) {
	cout << "Please input the number n: ";
	cin.get(n,100);
	cout << "Please input the number k: ";
	cin >> k;
	cout << "The result is: " << endl;
}

void setup(bool flag[], int &n_length, char n[], int k) {
	n_length = strlen(n);
	for (int i = 0; i < n_length; i++) {
		flag[i] = true;
	}
}

void output(char result[], int &counting, int k) {
	counting++;
	cout << counting <<")\t"<< result;
	cout << endl;
}

void binominal(char n[], int k, bool flag[], int i, int n_length, char result[], int &counting) {
	for (int j = 0; j < n_length; j++) {
		if (flag[j] == true) {
			result[i] = n[j];
			if (i == k-1) {
				output(result,counting, k);
			}
			else {
				flag[j] = false;
				binominal(n, k, flag, i + 1, n_length, result, counting);
				flag[j] = true;
			}
		}
	}
}

int main() {
	char n[100], result[100];
	bool flag[100];
	int k = 0, n_length = 0, counting = 0;
	input(n, k);
	result[k] = NULL;
	setup(flag, n_length, n, k);
	binominal(n, k, flag, 0, n_length, result, counting);
	return 0;
}