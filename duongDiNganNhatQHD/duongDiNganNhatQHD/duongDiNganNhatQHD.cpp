// duongDiNganNhatQHD.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
using namespace std;
int cost[100][100], f[100][100];

void input(int &n, int &m, int a, int b) {
	ifstream infile;
	infile.open("input.txt");
	infile >> n >> m;
	for (int i = 1; i <= m; ++i) {
		infile >> a >> b;
		infile >> cost[a][b];
		cost[b][a] = cost[a][b];
	}
	infile.close();
}

int min(int a, int b) {
	return (a < b) ? a : b;
}


void init(int n) {
	for (int i = 1; i <= n; ++i) {
		f[1][i] = cost[1][i];
	}
}

void dynamicProgramming(int n) {
	for (int i = 2; i <= n-1; ++i) {
		for (int j = i+1; j <= n; ++j) {
			if ((cost[i][j] != 0) && (f[i-1][i] != 0)) {
				if (f[i - 1][j] != 0) {
					f[i][j] = min(f[i - 1][i] + cost[i][j], f[i - 1][j]);
				}
				else {
					f[i][j] = f[i - 1][i] + cost[i][j];
				}
			}
			else {
				f[i][j] = f[i - 1][j];
			}
		}
	}
}

void recurrenceRelation(int n) {
	if (f[n - 1][n] == 0) {
		cout << "N/A" << endl;
	}
	else {
		int i = n - 1, j = n, count = 1, temp[100];
		temp[1] = n;
		while (i>1) {
			if (f[i][j] == f[i - 1][i] + cost[i][j]) {
				temp[++count] = i;
				j = i;
				--i;
			}
			else {
				--i;
			}
		}
		cout << f[n - 1][n] << endl;
		cout << 1;
		for (int i = count; i >= 1; --i) {
			cout << " --> " << temp[i];
		}
		cout << endl;
	}
}

int main()
{
	int n = 0, m = 0, a = 0, b = 0;
	input(n, m, a, b);
	init(n);
	dynamicProgramming(n);
	recurrenceRelation(n);
	return 0;
}

