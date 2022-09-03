// 6.1c.cpp : Defines the entry point for the console application.
//

#include <iostream>
using namespace std;

void input(double &n) {
	cout << "Moi thay nhap n: ";
	cin >> n;
}

double C(double n) {
	if (int(n) == 1) {
		return 1;
	}
	if (int(n) % 2 == 0) {
		return -1.0 / n + C(n - 1);
	}
	else {
		return 1.0 / n + C(n - 1);
	}
}

int main()
{	
	double n = 0;
	input(n);
	cout << "1 - 1/2 + 1/3 + ... + (+/-)1/n = " << C(n) << endl;
    return 0;
}

