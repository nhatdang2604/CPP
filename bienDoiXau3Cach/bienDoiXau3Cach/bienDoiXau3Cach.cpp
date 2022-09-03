// bienDoiXau3Cach.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int dp[255][255];

void input(string &x, string &y) {
	ifstream infile;
	infile.open("input.txt");
	getline(infile, x);
	getline(infile, y);
	infile.close();
}

int min(int a, int b) {
	if (a < b) {
		return a;
	}
	else {
		return b;
	}
}

void init(int n, int m) {
	dp[0][0] = 0;
	for (int i = 1; i <= n; ++i) {
		dp[i][0] = i;
	}
	for (int j = 1; j <= m; ++j) {
		dp[0][j] = j;
	}
}

void dynamicProgramming(string x, string y, int n, int m) {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (x[i-1] == y[j-1]) {
				dp[i][j] = dp[i - 1][j - 1];
			}
			else {
				dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
			}
		}
	}
}

int main() {
	string x, y;
	int x_length, y_length;
	input(x,y);
	x_length = x.length();
	y_length = y.length();
	init(x_length, y_length);
	dynamicProgramming(x, y, x_length, y_length);
	cout << dp[x_length][y_length] << endl;
    return 0;
}

