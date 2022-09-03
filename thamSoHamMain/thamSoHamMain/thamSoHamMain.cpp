// thamSoHamMain.cpp : Defines the entry point for the console application.
//

#include <iostream>
using namespace std;

int main(int agrc, char **agrv)
{
	cout << "Chuong trinh nay ten la:\n" << agrv[0] << endl;
	for (int i = 1; i < agrc; ++i) {
		cout << "agtv[" << i << "] = " << agrv[i] << endl;
	}
	return 0;
}

