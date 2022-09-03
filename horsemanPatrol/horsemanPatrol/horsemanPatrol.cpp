// horsemanPatrol.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
using namespace std;
int X[8] = { -2,-2,-1,-1,1,1,2,2 };
int Y[8] = { -1,1,-2,2,-2,2,-1,1 };
int n;
bool check[100][100];
int f[100][100];

void output()
{
	for (int x1 = 1; x1 <= n; x1++)
	{
		for (int y1 = 1; y1 <= n; y1++)
		{
			cout << f[x1][y1] << "\t";
		}
		cout << endl;
	}
	cout << endl << "--------------------------------------------------" << endl;
}

void backTracking(int x, int y, int count)
{
	for (int l = 0; l <= 7; l++)
	{
		if ((check[x + X[l]][y + Y[l]] == false) && (x + X[l] <= n) && (x + X[l] >= 1) && (y + Y[l] <= n) && (y + Y[l] >= 1))
		{
			f[x + X[l]][y + Y[l]] = count;
			if (count == n*n)
			{
				output();
			}
			else
			{
				check[x + X[l]][y + Y[l]] = true;
				backTracking(x + X[l], y + Y[l], count + 1);
				check[x + X[l]][y + Y[l]] = false;
				f[x + X[l]][y + Y[l]] = 0;
			}
		}
	}
}

int main()
{
	int x, y;
	cout << "Please input n (The chessboard will have size n x n ): ";
	cin >> n;
	cout << "Please input the start position: ";
	cin >> x >> y;
	f[x][y] = 1; check[x][y] = true;
	backTracking(x, y, 2);
	return 0;
}

