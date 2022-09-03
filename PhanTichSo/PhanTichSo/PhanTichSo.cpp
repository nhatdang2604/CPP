// PhanTichSo.cpp : Defines the entry point for the console application.
//

#include <iostream>
using namespace std;
int dp[100][100];

void input(int &n) {
	cout << "Nhap n:";
	cin >> n;
}

void init(int n) {
	for (int i = 1; i <= n; ++i) {
		dp[i][0] = 1;
		dp[0][i] = 0;
	}
	dp[0][0] = 1;
}

void dynamicProgramming(int n) {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (i > j) {
				dp[i][j] = dp[i - 1][j];
			}
			else {
				dp[i][j] = dp[i - 1][j] + dp[i][j - i];
			}
		}
	}
}

int main()
{
	int n = 0;
	input(n);
	init(n);
	dynamicProgramming(n);
	cout << dp[n][n] << endl;
	return 0;
}

