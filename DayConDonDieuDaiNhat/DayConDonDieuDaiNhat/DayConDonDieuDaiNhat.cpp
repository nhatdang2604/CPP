// DayConDonDieuDaiNhat.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
using namespace std;

void input(int &n, int a[])
{
	ifstream infile;
	infile.open("input.txt");
	infile >> n;
	for (int i = 1; i <= n; i++) {
		infile >> a[i];
	}
	infile.close();
}

void dp(int n, int a[], int f[]) {
	f[0] = 1;
	for (int i = 1; i <= n; i++) {
		f[i] = 1;
		for (int j = 1; j <= i - 1; j++) {
			if ((a[i] >= a[j]) && (f[i] < f[j] + 1)) {
				f[i] = f[j] + 1;
			}
		}
	}
}

void output(int n, int f[]) {
	ofstream outfile;
	outfile.open("output.txt");
	outfile << f[n];
	outfile.close();
}


int main()
{
	int n = 0, a[100], f[100];
	input(n, a);
	dp(n, a, f);
	output(n, f);
	return 0;
}

