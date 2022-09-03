// VSTEPS.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
using namespace std;
static long int dp[1000000];

bool input(int &n, int &k, int &x) {
	int temp = -1;
	ifstream infile;
	infile.open("input.txt");
	infile >> n >> k;
	for (int i = 1; i <= k; ++i) {
		infile >> x;
		if ((x - temp == 1) || (x == n)) {
			return false;
		}
		else {
			dp[x] = -1;
			temp = x;
			x = NULL;
		}
	}
	infile.close();
	return true;
}

void init() {
	dp[1] = 0;
	dp[2] = 1 * (dp[2] != -1) - 1 * (dp[2] == -1);
	dp[3] = 2 * ((dp[3] != -1) && (dp[2] != -1)) - 1 * (dp[3] == -1) + 1 * ((dp[3] != -1) && (dp[2] == -1));
}

void dynamicProgramming(int n) {
	for (int i = 4; i <= n; ++i) {
		(dp[i] == 0) ? dp[i] = (dp[i - 1] * (dp[i - 1] != -1) + dp[i - 2] * (dp[i - 2] != -1)) % 14062008 : dp[i] = -1;
	}
}

int main()
{
	int n = 0, k = 0, x=0;
	if (input(n, k, x) == false) {
		cout << 0 << endl;
	}
	else {
		init();
		dynamicProgramming(n);
		cout << dp[n] << endl;
	}
	return 0;
}

