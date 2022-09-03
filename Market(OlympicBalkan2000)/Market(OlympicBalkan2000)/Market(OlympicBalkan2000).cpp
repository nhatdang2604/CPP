// Market(OlympicBalkan2000).cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
using namespace std;
bool dp[100];

void input(int &n, int a[], int &sum) {
	ifstream infile;
	infile.open("input.txt");
	infile >> n;
	for (int i = 0; i < n; ++i) {
		infile >> a[i];
		sum += a[i];
	}
	infile.close();
}

int resultDynamicProgramming(int n, int a[], int sum) {
	int temp = 0;
	dp[0] = true;
	for (int i = 0; i < n; ++i) {
		for (int t = sum; t >= a[i]; --t) {
			if ((dp[t] == false) && (dp[t - a[i]] == true)) {
				dp[t] = true;
				++temp;
			}
		}
	}
	return temp;
}

int main()
{
	int n = 0, sum = 0, a[100];
	input(n, a, sum);
	cout << resultDynamicProgramming(n, a, sum) << endl;
	return 0;
}

