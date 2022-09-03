// 6.4b.cpp : Defines the entry point for the console application.
//

#include <iostream>
using namespace std;

#define MAX_CHARACTER 256

void input(char a[], int &k) {
	cout << "Moi thay nhap chuoi: ";
	cin.getline(a, MAX_CHARACTER);
	cout << "Moi thay nhap so chap k: ";
	cin >> k;
	cout << "Cac chinh hop chap " << k << " cua chuoi la: \n";
}

void combinationBacktracking(int j, int k, char result[], char a[], int length, bool *check) {
	for (int i = 0; i < length; ++i) {
		if (!check[i]) {
			check[i] = true;
			result[j] = a[i];
			if (j == k - 1) {
				cout << result << endl;
				check[i] = false;
			}
			else {
				combinationBacktracking(j + 1, k, result, a, length, check);
				check[i] = false;
			}
		}
	}
}

int main()
{
	char a[MAX_CHARACTER], result[MAX_CHARACTER];
	int k = 0;
	input(a, k);
	result[k] = NULL;
	int length = strlen(a);
	bool check[MAX_CHARACTER];
	memset(check, false, sizeof(check));
	combinationBacktracking(0, k, result, a, length, check);
	return 0;
}

