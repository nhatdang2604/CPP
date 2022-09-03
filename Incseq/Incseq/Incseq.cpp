// Incseq.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
using namespace std;
int a[100], f[100];

void input(int &n)
{
	ifstream infile;
	infile.open("Incseq.txt");
	infile >> n;
	for (int i = 1; i <= n; i++) {
		infile >> a[i];
	}
	infile.close();
}

void init(int n)
{
	f[0] = 0;
	f[1] = 1;
	for (int i = 2; i <= n; i++) {
		f[i] = 36500;
	}
}

int max(int n, int arr[]) {
	int temp = arr[1];
	for (int i = 2; i <= n; i++) {
		if (temp <= arr[i]) {
			temp = arr[i];
		}
	}
	return temp;
}

void dynamicProgramming(int n)
{
	for (int i = 1; i <= n; i++) {
		if (a[i] >= max(i - 1, a)) {
			f[i] = max(i - 1, f) + 1;
		}
		else {
			f[i] = f[i - 1];
		}
	}
}

int main()
{
	int n = 0;
	input(n);
	init(n);
	dynamicProgramming(n);
	cout << f[n] << endl;
	return 0;
}

