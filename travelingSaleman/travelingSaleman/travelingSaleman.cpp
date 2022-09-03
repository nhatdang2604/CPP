// travelingSaleman.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
using namespace std;

int a[100][100], bestConfig[100], minCost, n, m;

void input() {
	int x, y;
	ifstream fi("input.txt");
	fi >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i == j) {
				a[i][j] = 0;
			}
			else {
				a[i][j] = 26500;
			}
		}
	}
	for (int i = 1; i <= m; i++) {
		fi >> x;
		fi >> y;
		fi >> a[x][y];
		a[y][x] = a[x][y];
	}
	fi.close();
}

void setup(bool free[], int result[]) {
	for (int i = 2; i <= n; i++) {
		free[i] = true;
	}
	free[1] = false;
	minCost = 26500;
	result[1] = 1;
}

void updateResult(int k, int &l, int x[], int y[]) {
	l = k;
	for (int i = 1; i <= n; i++) {
		x[i] = y[i];
	}
}

void optimzeBackTracking(int i, bool free[], int &cost, int result[]) {
	for (int j = 2; j <= n; j++) {
		if ((free[j] == true) && (a[result[i-1]][j] < 26500) && (result[i-1] != j)) {
			cost += a[result[i-1]][j];
			result[i] = j;
			if ((i == n)&&(a[result[i]][1]<26500)) {
				cost += a[result[i]][1];
				if (cost < minCost) {
					updateResult(cost, minCost, bestConfig, result);
				}
				cost = cost - (a[result[i]][1] + a[result[i - 1]][j]);
			}
			else {
				free[j] = false;
				optimzeBackTracking(i + 1, free, cost, result);
				free[j] = true;
				cost -= a[result[i-1]][j];
			}
		}
	}
}

void output() {
	ofstream fo("output.txt");
	for (int i = 1; i <= n; i++) {
		fo << bestConfig[i] << " --> ";
	}
	fo << 1 << "\n";
	fo <<"cost: "<< minCost << "\n";
	fo.close();
}

int main()
{
	bool free[100];
	int result[100], cost = 0;
	input();
	setup(free, result);
	optimzeBackTracking(2, free, cost, result);
	output();
	return 0;
}

