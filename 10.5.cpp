#include <iostream>
using namespace std;
int bottomUpDP[100][100], topDownDP[100][100], a[100][100];

struct coordinates {
	int x, y;
};

void input(int &m, int &n) {
	cout << "- Moi thay nhap kich thuoc m x n \n\n";
	cout << "- Moi thay nhap m: ";
	cin >> m;
	cout << endl;
	cout << "- Moi thay nhap n: ";
	cin >> n;
	cout << endl;
	cout << "Moi thay nhap tung gia tri ruong tien (Theo thu tu tu tang tren cung xuong duoi, tu trai sang phai): \n\n";
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> a[m - i - 1][j];
		}
	}
	cout << endl;
}

int max(int a, int b) {
	return (a > b) ? a : b;
}

void init_BU(int m, int n) {
	for (int j = 0; j < n; ++j) bottomUpDP[0][j] = a[0][j];
}

void bottomUpSol(int m, int n) {
	for (int i = 1; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			if (j == 0) bottomUpDP[i][j] = max(bottomUpDP[i - 1][j], bottomUpDP[i - 1][j + 1]) + a[i][j];
			if (j == n-1) bottomUpDP[i][j] = max(bottomUpDP[i - 1][j], bottomUpDP[i - 1][j - 1]) + a[i][j]; 
			if (j != 0 && j != n - 1) bottomUpDP[i][j] = max(bottomUpDP[i - 1][j], max(bottomUpDP[i - 1][j - 1], bottomUpDP[i - 1][j + 1])) + a[i][j];
		}
	}
}


void recurrenceRelation_BU(coordinates trace[], int m, int n) {
	int count = 0;
	int max = bottomUpDP[m - 1][0];
	trace[0].x = m - 1;
	trace[0].y = 0;
	for (int j = 1; j < n; ++j) {
		if (max < bottomUpDP[m - 1][j]) {
			max = bottomUpDP[m - 1][j];
			trace[0].y = j;
		}
	}
	while (count != m - 1) {
		++count;
		int i = trace[count - 1].x;
		int j = trace[count - 1].y;
		trace[count].x = i - 1;
		if (bottomUpDP[i][j] == bottomUpDP[i - 1][j] + a[i][j]) trace[count].y = j;
		if ((j >= 1) && (bottomUpDP[i][j] == bottomUpDP[i - 1][j - 1] + a[i][j])) trace[count].y = j - 1;
		if ((j >= -1) && (bottomUpDP[i][j] == bottomUpDP[i - 1][j + 1] + a[i][j])) trace[count].y = j + 1;
	}
}

void bottomUp(coordinates trace[], int m, int n) {
	init_BU(m, n);
	bottomUpSol(m, n);
	recurrenceRelation_BU(trace, m, n);
	cout << "- Sau khi giai the huong bottom up, ket qua la: ";
	for (int i = m-1; i > 0; --i) {
		cout << "[" << trace[i].x << "][" << trace[i].y << "] --> ";
	}
	cout << "[" << trace[0].x << "][" << trace[0].y << "]" << endl << endl;
}

void init_TD(coordinates trace[], int m, int n) {
	memset(trace, 0, (m + 1)*(n + 1) * sizeof(coordinates));
	for (int j = 0; j < n; ++j) topDownDP[0][j] = a[0][j];
}

int topDownSol(int i, int j, int m, int n) {
	if (topDownDP[i][j] != 0) return topDownDP[i][j];
	if (j == 0) topDownDP[i][j] = max(topDownSol(i - 1, j, m, n), topDownSol(i - 1, j + 1, m, n)) + a[i][j];
	if (j == n - 1) topDownDP[i][j] = max(topDownSol(i - 1, j, m, n), topDownSol(i - 1, j - 1, m, n)) + a[i][j];
	if (j != 0 && j != n - 1) topDownDP[i][j] = max(topDownSol(i - 1, j, m, n), max(topDownSol(i - 1, j - 1, m, n), topDownSol(i - 1, j + 1, m, n))) + a[i][j];
	return topDownDP[i][j];
}

void recurrenceRelation_TD(coordinates trace[], int m, int n) {
	int count = 0;
	int max = topDownDP[m - 1][0];
	trace[0].x = m - 1;
	trace[0].y = 0;
	for (int j = 1; j < n; ++j) {
		if (max < topDownDP[m - 1][j]) {
			max = topDownDP[m - 1][j];
			trace[0].y = j;
		}
	}
	while (count != m - 1) {
		++count;
		int i = trace[count - 1].x;
		int j = trace[count - 1].y;
		trace[count].x = i - 1;
		if (topDownDP[i][j] == topDownDP[i - 1][j] + a[i][j]) trace[count].y = j;
		if ((j >= 1) && (topDownDP[i][j] == topDownDP[i - 1][j - 1] + a[i][j])) trace[count].y = j - 1;
		if ((j >= -1) && (topDownDP[i][j] == topDownDP[i - 1][j + 1] + a[i][j])) trace[count].y = j + 1;
	}
}

void topDown(coordinates trace[], int m, int n) {
	init_TD(trace, m, n);
	for (int i = 0; i < n; ++i) {
		topDownSol(m - 1, i, m, n);
	}
	recurrenceRelation_TD(trace, m, n);
	cout << "- Sau khi giai the huong top down, ket qua la: ";
	for (int i = m - 1; i > 0; --i) {
		cout << "[" << trace[i].x << "][" << trace[i].y << "] --> ";
	}
	cout << "[" << trace[0].x << "][" << trace[0].y << "]" << endl << endl;
}

int main() {
	coordinates trace[100 * 100];
	int n = 0, m = 0;
	input(m, n);
	bottomUp(trace, m, n);
	topDown(trace, m, n);
	return 0;
}