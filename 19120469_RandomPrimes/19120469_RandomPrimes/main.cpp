#include <iostream>
#include <time.h>
#include <vector>
using namespace std;

#define LOWER_BOUND_1 5
#define UPPER_BOUND_1 20
#define LOWER_BOUND_2 1
#define UPPER_BOUND_2 100

vector<int> randomizeIntegerNumbersFromRange(const int&, const int&, const int&);
void doQuestion1();
void doQuestion2(vector<int>&);
void doQuestion3(const vector<int>&);
void doQuestion4(const vector<int>&);
void doQuestion5(vector<int>&);
void printAllPrimes(const vector<int>&);
void printArray(const vector<int>&);
void removeAllOddNumbers(vector<int>&);
bool isPrime(const int&);
int sumAllPrimes(const vector<int>&);

vector<int> randomizeIntegerNumbersFromRange(const int& n, const int& min, const int& max) {
	vector<int> result(n);
	srand(unsigned int(time(NULL)));
	for (int i = 0; i < n; ++i) {
		result[i] = rand() % (max - min + 1) + min;
	}
	return result;
}

bool isPrime(const int& n) {
	if (n < 2) return false;
	if (n == 2) return true;
	if (n % 2 == 0) return false;
	for (int i = 3; i*i <= n; i += 2) {
		if (n % i == 0) return false;
	}
	return true;
}

void printAllPrimes(const vector<int> &arr) {
	for (unsigned int i = 0; i < arr.size(); ++i)
		if (isPrime(arr[i])) {
			cout << arr[i] << " ";
		}
	cout << endl;
}

int sumAllPrimes(const vector<int> &arr) {
	int result = 0;
	for (unsigned int i = 0; i < arr.size(); ++i) {
		if (isPrime(arr[i])) {
			result += arr[i];
		}
	}
	return result;
}

void removeAllOddNumbers(vector<int> &arr) {
	for (int i = arr.size() - 1; i >= 0; --i) {
		if (arr[i] % 2) {
			for (unsigned int j = i; j < arr.size() - 1; ++j) {
				arr[j] = arr[j + 1];
			}
			arr.pop_back();
		}
	}
}

void printArray(const vector<int>& arr) {
	for (unsigned int i = 0; i < arr.size(); ++i) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

void doQuestion1() {
	int n;
	cout << "Cau 1:\n";
	cout << "Moi thay nhap so phan tu de sinh mang ngau nhien co mien gia tri [5; 20]: ";
	cin >> n;
	vector<int> a = randomizeIntegerNumbersFromRange(n, LOWER_BOUND_1, UPPER_BOUND_1);
	cout << "Cac phan tu cua mang la:\n";
	printArray(a);
	cout << endl;
}

void doQuestion2(vector<int>& arr) {
	int m;
	cout << "Cau 2:\n";
	cout << "Moi thay nhap so phan tu de sinh mang ngau nhien co mien gia tri [1; 100]: ";
	cin >> m;
	arr = randomizeIntegerNumbersFromRange(m, LOWER_BOUND_2, UPPER_BOUND_2);
	cout << "Cac phan tu cua mang la:\n";
	printArray(arr);
	cout << endl;
}

void doQuestion3(const vector<int>& arr) {
	cout << "Cau 3 (Dung du kien o cau 2):\n";
	cout << "Cac phan tu la so nguyen to trong mang la:\n";
	printAllPrimes(arr);
	cout << endl;
}

void doQuestion4(const vector<int>& arr) {
	cout << "Cau 4 (Dung du kien o cau 2):\n";
	cout << "Tong cac so nguyen to trong mang la: ";
	cout << sumAllPrimes(arr) << endl;
	cout << endl;
}

void doQuestion5(vector<int>& arr) {
	cout << "Cau 5 (Dung du kien o cau 2):\n";
	cout << "Sau khi xoa cac phan tu le, mang tro thanh:\n";
	removeAllOddNumbers(arr);
	printArray(arr);
	cout << endl;
}

int main() {
	vector<int> arr;
	doQuestion1();
	doQuestion2(arr);
	doQuestion3(arr);
	doQuestion4(arr);
	doQuestion5(arr);
	system("PAUSE");
	return 0;
}