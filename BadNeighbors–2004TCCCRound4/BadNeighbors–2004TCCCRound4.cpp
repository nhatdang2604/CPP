// BadNeighbors–2004TCCCRound4.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
using namespace std;
int dp1[100], dp2[100];

/*
	NOTE: Đây là bài mà input ở dạng vòng tròn, phần tử thứ 1 tác động được tới phần tử thứ n, giải thuật giải quyết bằng cách khởi tạo 2 mảng:
		- Mảng thứ 1 gồm các phần tử từ 1 -> n-1 (bỏ phần tử n)
		- Mảng thứ 2 gồm các phần tử từ 2 -> n   (bỏ phần tử 1)
		  Tới đây chúng ta giải quyết bài toàn như trên 1 dãy đơn điệu bình thường
*/

void input(int &n, int arr[]) {
	ifstream infile;
	infile.open("input.txt");
	infile >> n;
	for (int i = 0; i < n; ++i) {
		infile >> arr[i];
	}
	infile.close();
} 

int max(int x, int y) {
	return (x > y) ? x : y;
}

void init(int n, int arr[]) {
	dp1[1] = arr[0];
	dp1[2] = max(arr[0], arr[1]);
	dp2[1] = arr[1];
	dp2[2] = max(arr[1], arr[2]);
}

void dynamicProgramming(int n, int arr[]) {
	for (int i = 3; i <= n - 1; ++i) {
		dp1[i] = dp1[i - 1];
		dp2[i] = dp2[i - 1];
		for (int j = 1; j <= i - 2; ++j) {
			if (dp1[i] < dp1[j] + arr[i - 1]) {
				dp1[i] = dp1[j] + arr[i - 1];
			}
			if (dp2[i] < dp2[j] + arr[i]) {
				dp2[i] = dp2[j] + arr[i];
			}
		} 
	}
}

int main()
{
	int n = 0, a[100];
	input(n, a);
	if (n == 1) {
		cout << a[0] << endl;
	}
	else {
		if (n == 2) {
			cout << max(a[0], a[1]) << endl;
		}
		else {
			if (n >= 3) {
				init(n, a);
				dynamicProgramming(n, a);
				cout << max(dp1[n - 1], dp2[n - 1]) << endl;
			}
		}
	}
	return 0;
}

