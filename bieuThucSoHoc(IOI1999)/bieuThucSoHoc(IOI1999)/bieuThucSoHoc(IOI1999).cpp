// bieuThucSoHoc(IOI1999).cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
using namespace std;
float dp[100][100];

void input(float arr[], int &n) {
	ifstream infile;
	infile.open("input.txt");
	infile >> n;
	for (int i = 0; i < n; ++i) {
		infile >> arr[i];
	}
	infile.close();
}

float operatorChosen(float a, float b) {
	return ((a + b) > (a*b)) ? a + b : a*b;
}

void init(float arr[], int n) {
	for (int i = 0; i < n; ++i) {
		dp[i][i] = arr[i];
		if (i < n - 1) {
			dp[i][i + 1] = operatorChosen(arr[i], arr[i + 1]);
		}
	}
}

void dynamicProgramming(float arr[], int n) {
	float max, temp;
	for (int i = n - 3; i >= 0; --i) {
		for (int j = i + 2; j < n; ++j) {
			max = -1;
			for (int k = i + 1; k <= j - 1; ++k) {
				temp = operatorChosen(dp[i][k], dp[k + 1][j]);
				if (max < temp) {
					max = temp;
				}
			}
			dp[i][j] = max;
		}
	}
}

int main()
{
	float a[100];
	int n = 0;
	input(a, n);
	init(a, n);
	dynamicProgramming(a, n);
	cout << dp[0][n - 1] << endl;
	return 0;
}

