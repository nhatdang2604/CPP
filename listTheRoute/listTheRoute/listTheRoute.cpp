
#include <iostream>
#include <fstream>
using namespace std;

ofstream OUTPUT("Output.txt");

void input(int a[][100], int &n, int &m, int &x, int &y) {
	int k, l;
	ifstream INPUT("Input.txt");
	INPUT >> n >> m;
	INPUT >> x >> y;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			a[i][j] = 0;
		}
	}
	for (int i = 1; i <= m; i++) {
		INPUT >> k;
		INPUT >> l;
		a[k][l] = 1;
		a[l][k] = 1;
	}
	INPUT.close();
}

void output(int result[], int finishPoint, int &counting) {
	int i = 0;
	counting++;
	OUTPUT << counting << ")\t";
	while (result[i] != finishPoint) {
		OUTPUT << result[i] << " --> ";
		i++;
	}
	OUTPUT << finishPoint << "\n";
}

void backTracking(int a[][100], int n, int i, int x, int y, int order, int result[], bool check[], int &counting, bool &flag) {
	for (int j = 1; j <= n; j++) {
		if ((check[j] == true) && (a[i][j] == 1)) {
			result[order] = j;
			if (j == y) {
				flag = true;
				output(result, y, counting);
			}
			else {
				check[j] = false;
				backTracking(a, n, j, x, y, order + 1, result, check, counting, flag);
				check[j] = true;
			}
		}
	}
}

int main() {
	int n = 0, m = 0, x = 0, y = 0, counting = 0, a[100][100], result[100];
	bool check[100], flag = false;
	input(a, n, m, x , y);
	for (int i = 1; i <= n; i++) {
		check[i] = true;
	}
	check[x] = false;
	result[0] = x;
	backTracking(a, n, x, x, y, 1, result, check, counting, flag);
	if (flag == false) {
		OUTPUT << "N/A\n";

	}
	OUTPUT.close();
	return 0;
}