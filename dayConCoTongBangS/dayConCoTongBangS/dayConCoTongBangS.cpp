// dayConCoTongBangS.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
using namespace std;
int a[100], f[100][100];

void input(int &n, int &s) {
	ifstream infile;
	infile.open("input.txt");
	infile >> n >> s;
	for (int i = 1; i <= n; i++) {
		infile >> a[i];
	}
	infile.close();
}

void init(int n, int s) {
	for (int i = 0; i <= n; i++) {
		f[i][0] = 1;
	}
	for (int j = 1; j <= s; j++) {
		f[0][j] = 0;
	}
}

void dynamicProgramming(int n, int s) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= s; j++) {
			if ((f[i - 1][j] == 1) || (f[i - 1][j - a[i]] == 1)) {
				f[i][j] = 1;
			}
			else {
				f[i][j] = 0;
			}
		}
	}
}

void recurrenceRelation(int n, int s) {
	int i = n, j = s, count = 0, result[100];
	if (f[n][s] == 0) {
		cout << "N/A" << endl;
	}
	else {
		do {
			while (f[i - 1][j] == 1) {
				i -= 1;
			}
			count++;
			result[count] = a[i];
			j -= a[i];
		} while ((i > 0) && (j > 0));
	}
	for (int i = count; i >= 1; i--) {
		cout << result[i] << " " ;
	}
	cout << endl;
}

int main()
{
	int n = 0, s = 0;
	input(n, s);
	init(n, s);
	dynamicProgramming(n, s);
	recurrenceRelation(n, s);
	return 0;
}

