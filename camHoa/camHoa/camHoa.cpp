// camHoa.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
using namespace std;
int dp[100][100], v[100][100];

void input(int &k, int &n) {
	ifstream infile;
	infile.open("input.txt");
	infile >> k >> n;
	for (int i = 0; i < k; ++i) {
		for (int j = 0; j < n; ++j) {
			infile >> v[i][j];
		}
	}
	infile.close();
}

int max(int a, int b) {
	return (a > b) ? a : b;
}

void init(int n) {
	int tempMax = v[0][0];
	for (int j = 0; j < n; ++j) {
		if (tempMax < v[0][j]) {
			tempMax = v[0][j];
		}
		dp[0][j] = tempMax;
	}
}

void dynamicProgramming(int k, int n) {
	for (int i = 1; i < k; ++i) {
		for (int j = 0; j < n; ++j) {
			if (i > j) {
				dp[i][j] = -1;
			}
			else {
				if (i == j) {
					for (int l = 0; l <= i; ++l) {
						dp[i][j] += v[l][l];
					}
				}
				else {
					dp[i][j] = max(dp[i - 1][j - 1] + v[i][j], dp[i][j - 1]);
				}
			}
		}
	}
	cout << dp[k-1][n-1] << endl;
}

void recurrenceRelation(int k, int n) {
	if (k == n) {
		for (int i = 0; i < n; ++i) {
			cout << i << " ";
		}
		cout << endl;
	}
	else {
		int count = -1, i = k - 1, j = n - 1, temp[100];
		while (count != k - 1) {
			if (i != 0) {
				if (i != j) {
					if (dp[i][j] == dp[i - 1][j - 1] + v[i][j]) {
						temp[++count] = j + 1;
						--i; --j;
					}
					else {
						--j;
					}
				}
				else {
					for (int l = i; l >= 0; l--) {
						temp[++count] = l + 1;
					}
					break;
				}
			}
			else {
				int maxTemp = dp[i][j];
				while (maxTemp == dp[i][j-1]) {
					--j;
				}
				temp[++count] = ++j;
			}
		}
		for (int i = count; i >= 0; --i) {
			cout << temp[i] << " ";
		}
		cout << endl;
	}
}

int main()
{
	int k = 0, n = 0;
	input(k, n);
	init(n);
	dynamicProgramming(k, n);
	recurrenceRelation(k, n);
	return 0;
}

