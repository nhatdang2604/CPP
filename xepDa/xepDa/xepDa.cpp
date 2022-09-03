// xepDa.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <fstream>
using namespace std;
int khoiDa[5000][4], dp1[5000], dp2[5000];

void swap(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}

void decreaseAscendingForAll(int n) {
	for (int i = 1; i <= n - 1; i++) {
		for (int j = i + 1; j <= n; j++) {
			if ((khoiDa[i][1] * khoiDa[i][2]) <= (khoiDa[j][1] * khoiDa[j][2])) {
				for (int k = 0; k <= 3; k++) {
					swap(khoiDa[i][k], khoiDa[j][k]);
				}
			}
		}
	}
}

void decreaseAscending(int k) {
	for (int i = 1; i <= 2; i++) {
		for (int j = i + 1; j <= 3; j++) {
			if (khoiDa[k][i] < khoiDa[k][j]) {
				swap(khoiDa[k][i], khoiDa[k][j]);
			}
		}
	}
}

void input(int &n) {
	ifstream infile;
	infile.open("input.txt");
	infile >> n;
	for (int i = 1; i <= n; i++) {
		infile >> khoiDa[i][1] >> khoiDa[i][2] >> khoiDa[i][3];
		khoiDa[i][0] = i;
		decreaseAscending(i);
	}
	infile.close();
}

void recurrenceRelation_nhieuNhat(int n, int arr[], int flag, int max) {
	int result[5000], count = 1;
	result[1] = flag;
	while (count!=max) {
		for (int i = flag - 1; i >= 1; i--) {
			if (((khoiDa[flag][1] <= khoiDa[i][1]) && (khoiDa[flag][2] <= khoiDa[i][2])) && (arr[flag] == arr[i] + 1)) {
				count++;
				result[count] = i;
				flag = i;
				break;
			}
		}
	}
	for (int i = count; i >= 1; i--) {
		cout << khoiDa[result[i]][0] << "\t" << khoiDa[result[i]][1] << "\t" << khoiDa[result[i]][2] << "\t" << khoiDa[result[i]][3] << endl;
	}
	cout << "\n*\t*\t*\t*\n\n";
}

void recurrenceRelation_caoNhat(int n, int arr[], int flag) {
	int result[5000], count = 1, high = khoiDa[flag][3];
	result[1] = flag;
	while (high != arr[n]) {
		for (int i = flag - 1; i >= 1; i--) {
			if (((khoiDa[flag][1] <= khoiDa[i][1]) && (khoiDa[flag][2] <= khoiDa[i][2])) && (arr[flag] == arr[i] + khoiDa[flag][3])) {
				count++;
				high += khoiDa[i][3];
				result[count] = i;
				flag = i;
				break;
			}
		}
	}
	cout << count << endl;
	for (int i = count; i >= 1; i--) {
		cout << khoiDa[result[i]][0] << "\t" << khoiDa[result[i]][1] << "\t" << khoiDa[result[i]][2] << "\t" << khoiDa[result[i]][3] << endl;
	}
}

void dynamicProgramming(int n, int arr1[],int arr2[], int &flag, int &max) {
	for (int i = 1; i <= n; i++) {
		arr1[i] = 1;
		arr2[i] = khoiDa[i][3];
		for (int j = 1; j <= i - 1; j++) {
			if ((khoiDa[i][1] <= khoiDa[j][1]) && (khoiDa[i][2] <= khoiDa[j][2])) {
				if (arr1[i] < arr1[j] + 1) {
					arr1[i] = arr1[j] + 1;
				}
				if (arr2[i] < arr2[j] + khoiDa[i][3]) {
					arr2[i] = arr2[j] + khoiDa[i][3];
				}
			}
		}
		if (max < arr1[i]) {
			max = arr1[i];
			flag = i;
		}
	}
	cout << max << endl;
}

int main()
{
	int n = 0, flag = 0, max = 0;
	input(n);
	decreaseAscendingForAll(n);
	dynamicProgramming(n, dp1, dp2, flag, max);
	recurrenceRelation_nhieuNhat(n, dp1, flag, max);
	recurrenceRelation_caoNhat(n, dp2, n);
	return 0;
}

