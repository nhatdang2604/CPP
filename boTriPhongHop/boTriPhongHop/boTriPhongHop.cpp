// boTriPhongHop.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
using namespace std;

void input(int &n, int s[], int f[]) {
	ifstream infile;
	infile.open("input.txt");
	infile >> n;
	for (int i = 1; i <= n; i++) {
		infile >> s[i] >> f[i];
	}
	infile.close();
}

void output(int result) {
	ofstream outfile;
	outfile.open("output.txt");
	outfile << result;
	outfile.close();
}

void swap(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}

void increaseAscending(int n, int s[], int f[]) {
	for (int i = 1; i <= n-1; i++) {
		for (int j = i + 1; j <= n; j++) {
			if (f[i] > f[j]) {
				swap(f[i], f[j]);
				swap(s[i], s[j]);
			}
		}
	}
}

void dynamicProgramming(int n, int s[], int f[]) {
	int dp[100], max = 0;
	for (int i = 1; i <= n; i++) {
		dp[i] = 1;
		for (int j = 1; j <= i - 1; j++) {
			if ((s[i] >= f[j]) && (dp[i] < dp[j] + 1)) {
				dp[i] = dp[j] + 1;
			}
		}
		if (max < dp[i]) {
			max = dp[i];
		}
	}
	output(max);
}

int main()
{
	int n = 0, s[100], f[100];
	input(n, s, f);
	increaseAscending(n, s, f);
	dynamicProgramming(n, s, f);
	return 0;
}

