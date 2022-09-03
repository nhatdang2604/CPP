// 6.3d.cpp : Defines the entry point for the console application.
//

#include <iostream>
using namespace std;

#define MAX_ELEMENT 100

void input(int &n, int a[]) {
	cout << "Moi thay nhap so phan tu cua mang ( <= 100 ): ";
	cin >> n;
	cout << "Moi thay nhap cac phan tu (VD: n=3, nhap: 4 2 1): ";
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
}

bool primeCheck(int n) {
	if (n < 2) return false;
	if (n == 2) return true;
	if (n > 2 && n % 2 == 0) return false;
	for (int i = 3; i*i <= n; ++i) {
		if (n % i == 0) return false;
	}
	return true;
}

void printPrime(int a[], int l, int r) {
	if (l == r) {
		if (primeCheck(a[l])) cout << a[l] << " ";
		return;
	}
	int mid = (l + r) / 2;
	printPrime(a, l, mid);
	printPrime(a, mid + 1, r);
}

int main()
{
	int a[MAX_ELEMENT], n = 0;
	input(n, a);
	cout << "Cac so nguyen to trong mang la: ";
	printPrime(a, 0, n - 1);
	cout << endl;
    return 0;
}

