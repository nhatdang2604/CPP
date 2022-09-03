// 6.2b.cpp : Defines the entry point for the console application.
//

#include <iostream>
using namespace std;

void input(int &n) {
	cout << "Moi thay nhap chieu cao cua tam giac Pascal: ";
	cin >> n;
}

int C(int n, int k) {
	if (k == n || k == 1 || n == 1) return 1;
	return C(n - 1, k - 1) + C(n - 1, k);
}

void printPascalTriagle(int n) {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= i; ++j) {
			cout << C(i, j) << "\t";
		}
		cout << "\n";
	}
}

int main()
{
	int n = 0;
	input(n);
	printPascalTriagle(n);
	return 0;
}

