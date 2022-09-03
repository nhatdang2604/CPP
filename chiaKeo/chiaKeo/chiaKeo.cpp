// chiaKeo.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
using namespace std;
bool dp[100][100];

void input(int &n,int &sum, int arr[]){
	ifstream infile;
	infile.open("input.txt");
	infile >> n;
	for (int i = 1; i <= n; ++i) {
		infile >> arr[i];
		sum += arr[i];
	}
	infile.close();
}

void init(int n, int sum) {
	for (int i = 0; i <= n; ++i) {
		dp[i][0] = true;
	}
}

void dynamicProgramming(int n, int sum, int &flag, int arr[]) {
	int half = sum / 2;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= half; ++j) {
			if ((j >= arr[i]) && ((dp[i - 1][j - arr[i]]==true) || (dp[i - 1][j]==true))) {
				dp[i][j] = true;
				flag = j;
			}
		}
	}

}

int main()
{
	int sum = 0, n = 0, flag = 0, a[100];
	input(n, sum, a);
	init(n, sum);
	dynamicProgramming(n, sum, flag, a);
	cout << flag << " " << sum - flag << endl;
	return 0;
}

