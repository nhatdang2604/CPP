// Carrot.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
int dp[100];

void init(int k, int n) {
	memset(dp, 0, sizeof(dp));
}

void dynamicProgramming(int k, int n) { //Day chinh la bai toan di len n bac thang co ban !!!!!!!!!!!!!
	for (int i = 1; i <= k; ++i) {
		for (int j = 1; j <= i-1; ++j) {
			dp[i] += dp[j];
		}
		++dp[i];
	}
	for (int i = k + 1; i <= n; ++i) {
		for (int j = 1; j <= k; ++j) {
			dp[i] += dp[i-j];
		}
	}
}

void input(int t, int k, int n) {
	ifstream infile;
	infile.open("input.txt");
	infile >> t;
	for (int i = 1; i <= t; ++i) {
		infile >> k >> n;
		init(k, n);
		dynamicProgramming(k, n);
		cout << dp[n] << endl;
		k = NULL; n = NULL;
	}
	infile.close();
}


int main()
{
	input(0, 0, 0);
	return 0;
}

