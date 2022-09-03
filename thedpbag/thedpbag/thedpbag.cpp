// thedpbag.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int f[50][50],v[50],w[50],n,s;
bool q[50];

//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------

void dynamicProgramingForTheBag()									//Quy hoach dong
{
	for (int i=1; i<=n; i++)
		for (int j = 1; j <= s; j++)
		{
			f[i][j] = f[i - 1][j];
			if (j >= w[i])
				if (f[i - 1][j]<v[i] + f[i - 1][j - w[i]])
					f[i][j] = v[i] + f[i - 1][j - w[i]];		
		}
}

//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------

void recurrenceRelationForTheBag()									//Truy vet
{
	int i = n, j = s;
	while ((i != 0) && (j != 0))
		if (f[i][j] ==v[i]+f[i - 1][j - w[i]])
		{
			q[i] = true;
			i = i - 1;
			j = j - w[i];
		}
		else
			i = i - 1;
}

//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------

int main()
{
	cout << "Select the number of the items: ";
	cin >> n;
	cout << endl;
	cout << "Select the weight that you can take: ";
	cin >> s;
	cout << endl;
	cout << "Please input the weight of each items: ";
	for (int i = 1; i <= n; i++)
		cin >> w[i];
	cout << endl;
	cout << "Please input the value of each items:  ";
	for (int i = 1; i <= n; i++)
		cin >> v[i];
	cout << endl << "---------------------------------------------------------------------\n\n";
	dynamicProgramingForTheBag();
	recurrenceRelationForTheBag();
	cout << "The maximum value that you can take: " << f[n][s] << endl;
	for (int i = 1; i <= n; i++)
		if (q[i] == true)
			cout << "You take the item number #" << i << endl;
	return 0;
}

