// backtracking.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

bool check[10];
int output[10], input[10];

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

void backtracking(int count, int n)
{
	for (int i = 1; i <= n; i++)					//just backtracking 
		if (check[i] == true)
		{
			output[count] = input[i];
			if (count == n)
			{
				for (int j = 1; j <= n; j++)
				{
					cout << output[j];
				}
				cout << endl;
			}
			else
			{
				check[i] = false;
				backtracking(count + 1, n);
				check[i] = true;
			}
		}
}


//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------


int setup(int target)			
{
	int i,n=0;
	i = target % 10;
	while (i != 0)						// divide number into degits and stack them into array
	{
		n += 1;
		input[n] = i;
		target = target / 10;
		i = target % 10;
	}
	for (i = 1; i <= n; i++)			// setup bool array for process
		check[i] = true;
	return n;
}

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

int main()
{
	int count, target,i;
	cout << "Please choose one number which has different digits:  "; cin >> target;
	backtracking(1, setup(target));
	return 0;
	
}


