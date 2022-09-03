// LongestCommonSubsequence(LCS).cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
using namespace std;
using std::string;

int f[50][50];
string a, b, c;

void dynamicProgramming()
{
	for (int i = 0; i < a.length(); i++)
		for (int j = 0; j < b.length(); j++)
			if (a[i] == b[j])
				f[i+1][j+1] = f[i][j] + 1;
			else
				if (f[i][j+1] >= f[i+1][j])
					f[i+1][j+1] = f[i][j+1];
				else
					f[i+1][j+1] = f[i+1][j];
}

void recurrenceRelation()
{
	int i = a.length()-1, j = b.length()-1;
	while ((i >= 0)&&(j >= 0))
	{
		if (a[i] == b[j])
		{
			c += a[i];
			i -= 1;
			j -= 1;
		}
		else
			if (f[i+1][j+1] == f[i][j+1])
				i -= 1;
			else
				j -= 1;
	}
}

int main()
{
	cout << "Please input the first string:  ";
	cin >> a;
	cout << "Please input the second string: ";
	cin >> b;
	dynamicProgramming();
	recurrenceRelation();
	cout <<"The longest common subsequence has the length: "<<f[a.length()][b.length()] << endl;
	cout << "The longest common subsequence is: ";
	for (int i = c.length()-1; i >= 0; i--)
		cout << c[i];
	cout << endl;
	return 0;
}

