#include<iostream>
#include"RandomYear.h"
using namespace std;

void testNumberGenerator() {
	cout << "1.) Xuat so nguyen n ngau nhien nam trong doan [5, 20]\n";
	cout << "- So ngau nhien co duoc la: ";
	cout << randomizeAnIntegerFromRange(5, 20) << endl;
	cout << endl;
}

void testYearGenerator(vector<int>& result) {
	int n;
	cout << "2. Xuat n nam ngau nhien (nam >= 1900):\n";
	cout << "- Moi thay nhap so nam: ";
	cin >> n;
	result = randomizeYears(n, 1900);
	cout << "- Cac nam co duoc la: ";
	for (unsigned int i = 0; i < result.size(); ++i) {
		cout << result[i] << " ";
	}
	cout << endl << endl;
}

void testLeapYearCounter(const vector<int>& result) {
	cout << "3.) Dem so nam nhuan\n";
	cout << "- So nam nhuan co duoc la: " << countLeapYears(result) << endl;
}

int main() {
	vector<int>result;
	testNumberGenerator();
	testYearGenerator(result);
	testLeapYearCounter(result);
	system("PAUSE");
	return 0;
}