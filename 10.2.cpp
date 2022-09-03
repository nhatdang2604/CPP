#include <iostream>
using namespace std;

#define MAX_ELEMENT 256

void input(int a[], int &n) {
	cout << "Moi thay nhap so phan tu cua mang: ";
	cin >> n;
	cout << endl;
	cout << "Moi thay nhap cac phan tu trong mang (VD: so phan tu: 3, cac phan tu: 9, 2, 1. Nhap: 9 2 1)\n\n";
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	cout << endl;
}

void init_bottomUp(int dp[], int trace[], int n) {
	dp[0] = 0;
	dp[1] = 1;
	trace[1] = 1;
	memset(trace, 0, n * sizeof(int));
}


void bottomUpSol(int dp[], int a[], int trace[], int n) {
	int maxLIS;
	for (int i = 2; i <= n; ++i) {
		maxLIS = 0;
		for (int j = 1; j < i; ++j) {
			if (a[i] > a[j] && dp[maxLIS] < dp[j] + 1) maxLIS = j;
		}
		dp[i] = dp[maxLIS] + 1;
		trace[i] = maxLIS;
	}
}

 
int findMax(int dp[], int n) {
	int max = 0;
	for (int i = 1; i <= n; ++i) {
		if (dp[max] < dp[i]) max = i;
	}
	return max;
}

void recurrenceRelation(int dp[], int n, int trace[], int a[]) {
	int result[MAX_ELEMENT];
	int m = 0;
	int pivot = findMax(dp, n);
	result[m] = a[pivot];
	while (pivot > 0) {
		++m;
		result[m] = a[trace[pivot]];
		pivot = trace[pivot];
	}
	cout << "ket qua la: ";
	for (int i = m-1; i >=0; --i) {
		cout << result[i] << " ";
	}
	cout << endl << endl;
}

void bottomUp(int bottomUpDP[], int a[], int trace[], int n) {
	init_bottomUp(bottomUpDP, trace, n);
	bottomUpSol(bottomUpDP, a, trace, n);
	cout << "- Theo huong bottom up, ";
	recurrenceRelation(bottomUpDP, n, trace, a);
}

void init_topDown(int dp[], int trace[], int n) {
	memset(dp, -1, (n + 1) * sizeof(int));
	memset(trace, -1, (n + 1) * sizeof(int));
	dp[0] = 0;
	dp[1] = 1;
}

int topDownSol(int dp[], int n, int trace[], int a[]) {
	if (dp[n]!=-1) return dp[n];
	int max = 1;
	for (int i = 1; i < n; i++){
		dp[i] = topDownSol(dp, i, trace, a);
		if (a[i] < a[n] && dp[i] + 1 > max) {
			max = dp[i] + 1;
			trace[n] = i;
		}
	}
	dp[n] = max;
	return max;
}

void topDown(int topDownDP[], int a[], int trace[], int n) {
	init_topDown(topDownDP, trace, n);
	topDownSol(topDownDP, n, trace, a);
	cout << "- Theo huong top down, ";
	recurrenceRelation(topDownDP, n, trace, a);
}


int main() {
	int a[MAX_ELEMENT];
	int topDownDP[MAX_ELEMENT];
	int	bottomUpDP[MAX_ELEMENT];
	int	trace[MAX_ELEMENT];
	int n = 0, count = 0;

	input(a, n);
	bottomUp(bottomUpDP, a, trace, n);
	topDown(topDownDP, a, trace, n);
	return 0;
}