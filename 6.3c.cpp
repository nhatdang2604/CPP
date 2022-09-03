// 6.3c.cpp : Defines the entry point for the console application.
//

#include <iostream>
using namespace std;

#define MAX_ELEMENT 100

void input(int &n, int &x, int a[]) {
	cout << "Chu y: Neu mang co nhieu phan tu can tim, chuong trinh se xuat ra vi tri dau tien\n\n";
	cout << "Moi thay nhap so phan tu cua mang ( <= 100 ): ";
	cin >> n;
	cout << "Moi thay nhap cac phan tu (VD: n=3, nhap: 4 2 1): ";
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	cout << "Moi thay nhap phan tu can tim: ";
	cin >> x;
}

int search(int x, int a[], int l, int r) {
	if (l == r) return (a[l] == x )? l : -1;
	int mid = (l + r) / 2;
	int index1 = search(x, a, l, mid);
	int index2 = search(x, a, mid + 1, r);
	int index = -1;
	if (a[index2] == x) index = index2;
	if (a[index1] == x) index = index1;
	return index;
}

int main()
{
	int n = 0, x = 0, a[MAX_ELEMENT];
	input(n, x, a);
	int index = search(x, a, 0, n - 1);
	if (index != -1) {
		cout << x << " chinh la a[" << index << "]" << endl;
	}
	else {
		cout << "Khong tim thay !\n";
	}
	return 0;
}

