// 01TwiceTime.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;
int n, a[100];

void print()
{
	for (int x = 1; x <= n; x++)
	{
		cout << a[x];
	}
	cout << endl;
}

int main()
{
	int i, j, l, k, x;
	cout << "Please enter the number of digits : ";
	cin >> n;
	if (n < 4)
	{
		cout << "N/A" << endl;
		return 0;
	}
	a[0] = 2; a[n + 1] = 2; 
	i = n - 2;
	while (i > 1)
	{
		for (int j = 1; j <= n; j++)
		{
			a[j] = 0;
		}
		a[i] = 1;
		for (int j = n; j >= i + 2; j--)
		{
			for (int x = 1; x <= n; x++)
			{
				if (x != i)
				{
					a[x] = 0;
				}
			}
			a[j] = 1;
			l = n;
			while (l > 0)
			{
				print();
				l = n;
				while ((l > 0) && (((l == i) || (l == i - 1) || (l == j) || (l == j - 1)) || (a[l] == 1) || ((a[l] == 0) && (a[l - 1] == 0))))
				{
					if ((l == i) || (l == i - 1) || (l == j) || (l == j - 1))
					{
						l -= 2;
					}
					else
					{
						if ((a[l] == 1) || ((a[l] == 0) && (a[l - 1] == 0)))
						{
							l -= 1;
						}
					}
				}
				if ((l > 0) && (a[l] == 0) && (a[l - 1] != 0))
				{
					a[l] = 1;
					for (int x = l + 1; x <= n; x++)
					{
						if ((x != i) && (x != i - 1) && (x != j) && (x != j - 1))
						{
							a[x] = 0;
						}
					}
				}
			}
		}
		a[i] = 0;
		i--;
	}
	return 0;
}
