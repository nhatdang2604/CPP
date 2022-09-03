// farmer(IOI2004).cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
using namespace std;
int dp[4000][1500];

void input(int &n, int &Q, int v[], int w[])
{
	int M, K;
	ifstream infile;
	infile.open("input.txt");
	infile >> Q >> M >> K;
	n = M + K;
	for (int i = 1; i <= M; ++i) {
		infile >> w[i];
		v[i] = w[i];
	}
	for (int i = M + 1; i <= M + K; ++i) {
		infile >> w[i];
		v[i] = w[i] - 1;
	}
	infile.close();
}

void init(int n, int Q) {
	for (int i = 1; i <= n; ++i) {
		dp[i][0] = 0;
	}
	for (int j = 0; j <= Q; ++j) {
		dp[0][j] = 0;
	}
}

int max(int a, int b) {
	int temp = (a > b) ? a : b;
	return temp;
}

void dynamicProgramming(int n, int Q, int v[], int w[])
{
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= Q; ++j) {
			if (j - w[i] >= 0) {
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i]] + v[i]);
			}
			else {
				dp[i][j] = dp[i - 1][j];
			}
		}
	}
}

int main()
{
	int Q = 0, n = 0, v[2000], w[2000];
	input(n, Q, v, w);
	init(n, Q);
	dynamicProgramming(n, Q, v, w);
	cout << dp[n][Q] << endl;
	return 0;
}

