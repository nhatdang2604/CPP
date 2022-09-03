// ZigZag–2003TCCCSemifinals3.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
using namespace std;
int dp[100][2];

void input(int &n, int arr[]) {
	ifstream infile;
	infile.open("input.txt");
	infile >> n;
	for (int i = 0; i < n; ++i) {
		infile >> arr[i];
	}
	infile.close();
}

void dynamicProgramming(int n, int arr[]) {
	dp[0][1] = 1;
	dp[0][0] = 1;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < i; ++j) {
			if (arr[i] > arr[j]) {
				if (dp[i][1] < dp[j][0] + 1) {
					dp[i][1] = dp[j][0] + 1;
				}
			}
			else {
				if (arr[i] < arr[j]) {
					if (dp[i][0] < dp[j][1] + 1) {
						dp[i][0] = dp[j][1] + 1;
					}
				}
			}
		}
	}
}

int main()
{
	int n = 0, a[100];
	input(n, a);
	dynamicProgramming(n, a);
	int result = (dp[n - 1][1] > dp[n - 1][0]) ? dp[n - 1][1] : dp[n - 1][0];
	cout << result << endl;
	return 0;
}

