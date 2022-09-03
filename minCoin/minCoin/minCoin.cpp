// minCoin.cpp : Defines the entry point for the console application.
//

#include "iostream"
#include "fstream"
using namespace std;
int f[100][100], v[100];

void input(int &n, int &s)
 {
	ifstream infile;
	infile.open("input.txt");
	infile >> n >> s;
	for (int i = 1; i <= n; i++) {
		infile >> v[i];
	}
	infile.close();
}

int min(int a, int b) {
	int result;
	result = (a < b) ? a : b ;
	return result;
}


void init(int n, int s, int quantity[100])
{
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= s; j++) {
			f[i][j] = 36500;
		}
	}
	for (int i = 1; i <= n; i++) {
		f[i][0] = 0;
		quantity[i] = 0;
	}
	for (int j = 1; j <= s; j++) {
		f[0][j] = 36500;
	}
	f[0][0] = 0;

}

void dynamicProgramming(int n, int s)
{
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= s; j++) {
			if (j >= v[i]) {
				f[i][j] = min(f[i - 1][j], f[i][j - v[i]] + 1);
			}
			else {
				f[i][j] = f[i - 1][j];
			}
		}
	}
}

void recurrentRelation(int n, int s, int quantity[])
{
	int i = n, j = s;
	while ((i > 0) && (j > 0)) {
		if ( (j>=v[i]) && (f[i][j - v[i]] + 1 <= f[i-1][j]) ) {
			quantity[i] += 1;
			j -= v[i];
		}
		else {
			i -= 1;
		}
	}
}

int main()
{
	int n, s, quantity[100];
	input(n, s);
	init(n, s, quantity);
	dynamicProgramming(n, s);
	recurrentRelation(n, s, quantity);
	cout << f[n][s] << endl;
	for (int i = 1; i <= n; i++) {
		cout << quantity[i] << " dong " << v[i] << "VND" << endl;
	}
	return 0;
}

