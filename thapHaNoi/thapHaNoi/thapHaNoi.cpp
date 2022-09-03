// thapHaNoi.cpp : Defines the entry point for the console application.
//

#include <iostream>
using namespace std;

void input(int &n) {
	cout << "Moi thay nhap so dia: ";
	cin >> n;
}

void moveDisk(int n, char source, char dest, char auxiliary) {
	if (n == 1) {
		cout << "Chuyen dia tren cung tu cot " << source << " sang cot " << dest << endl;
	}
	else {
		moveDisk(n - 1, source, auxiliary, dest);
		cout << "Chuyen dia tren cung tu cot " << source << " sang cot " << dest << endl;
		moveDisk(n - 1, auxiliary, dest, source);
	}
}

int main()
{
	int n = 0;
	char a = 'A', b = 'B', c = 'C';
	input(n);
	cout << "Day la qua trinh chuyen " << n << " dia tu cot A sang cot C:\n";
	moveDisk(n, a, c, b);
	return 0;
}

