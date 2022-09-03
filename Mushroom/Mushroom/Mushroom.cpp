// Mushroom.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
using namespace std;
int a[100][100], all[100][100], x[100][100], y[100][100];

void input(int &n, int &m) {
	ifstream infile;
	infile.open("input.txt");
	infile >> n >> m;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			infile >> a[i][j];
		}
	}
	infile.close();
}

void dynamicProgramming(int n, int m) {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if ((i==1) && (j==1)) {
				all[1][1] = 1;
				x[1][1] = 1;
				y[1][1] = 1;
			}
			else {
				if (a[i][j] == -1) {
					all[i][j] == 0;
					x[i][j] == 0;
					y[i][j] == 0;
				}
				else {
					all[i][j] = all[i - 1][j] + all[i][j - 1];
					if (a[i][j] != a[n][m - 1]) {
						x[i][j] == 0;
					}
					else {
						x[i][j] = x[i - 1][j] + x[i][j - 1];
					}
					if (a[i][j] != a[n - 1][m]) {
						y[i][j] == 0;
					}
					else {
						y[i][j] = y[i - 1][j] + y[i][j - 1];
					}
				}
			}
		}
	}
}


int main()
{
	int n = 0, m = 0;
	input(n, m);
	dynamicProgramming(n, m);
	cout << all[n][m] - x[n][m - 1] - y[n - 1][m] << endl;
	return 0;
}

