// 6.3a.cpp : Defines the entry point for the console application.
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

int sum(int a[], int l, int r) {
	if (l == r) return a[l] % 2 == 0 ? a[l] : 0;
	int mid = (l + r) / 2;
	int tongL = sum(a, l, mid);
	int tongR = sum(a, mid + 1, r);
	return tongL + tongR;
}


int main()
{
	int n = 0, a[MAX_ELEMENT];
	input(n, a);
	cout << "Tong cac so chan trong mang la: " << sum(a, 0, n - 1) << endl;
    return 0;
}

