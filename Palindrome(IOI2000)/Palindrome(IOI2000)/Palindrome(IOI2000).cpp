// Palindrome(IOI2000).cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int dp[255][255];

void input(string &s) {
	ifstream infile;
	infile.open("input.txt");
	getline(infile, s);
	infile.close();
}

int min(int a, int b) {
	return (a < b) ? a : b;
}

void init(string s, int n) {
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= n; ++j) {
			if (i != j) {
				dp[i][j] = 36500;
			}
			else {
				dp[i][j] = 0;
			}
		}
	}
}

void dynamicProgramming(string s, int n) {
	for (int i = n-1; i>=1; --i) {
		for (int j = i+1; j <= n; ++j) {
			if (s[i-1] == s[j-1]) {
				dp[i][j] = dp[i + 1][j - 1];
			}
			else {
				dp[i][j] = min(dp[i + 1][j], dp[i][j - 1]) + 1;
			}
		}
	}
}

int main() {
	string s;
	input(s);
	int s_length = s.length();
	init(s, s_length);
	dynamicProgramming(s, s_length);
	cout << dp[1][s_length] << endl;
	return 0;
}

