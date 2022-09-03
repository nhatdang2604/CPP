// thequeenproblem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <math.h>

using namespace std;

int n,x_temp[50],y_temp[50],counting;
bool field[50][50], fieldcheck[50][50], button;

bool testing(int x, int j) //The method to check the queen if it's legal
{
	for (int i = 0; i <= x - 1; i++)
	{
		if ((x_temp[i] == x) || (y_temp[i] == j) || (abs(x_temp[i] - x) == abs(y_temp[i] - j)))
			return 0;
	}
	return 1;
}

void backtrackingForTheQueen(int x) // Backtracking alogrithm 
{
	for(int j = 1; j <= n; j++)
	{
		if (fieldcheck[x][j] == false)
		{
			if (testing(x,j) == 1)
			{
				x_temp[x] = x;
				y_temp[x] = j;
				field[x][j] = true;
				if (x == n)
				{
					counting += 1;
					cout << "The solution number " << counting << ": \n";
					button = 1;
					cout << endl;
					for (int row = 1; row <= n; row++)
					{
						for (int columm = 1; columm <= n; columm++)
						{
							cout << field[row][columm] << " ";
						}
						cout << endl;
					}
					field[x][j] = false;
					cout << endl;
					cout << "------------------------------------------------";
					cout << endl;
				}
				else
				{
					fieldcheck[x][j] = true;
					backtrackingForTheQueen(x + 1);
					field[x][j] = false;
					fieldcheck[x][j] = false;
					
				}
			}

		}
	}
}

int main()
{
	cout << "Please choose the number of the queens :  ";
	cin >> n;
	cout << "------------------------------------------------";
	button = 0; counting = 0;
	x_temp[0] = 132;
	y_temp[0] = 123;
	for (int i = 1; i <= n; i++)
	{
		x_temp[i] = 0;
		y_temp[i] = 0;
	}
	backtrackingForTheQueen(1);
	if (button == 0)
		cout << "khong co dap an!" << endl;
	return 0;
}