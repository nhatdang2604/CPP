#include <Integer.h>
#include <Random.h>
#include <DynamicArray.h>
#include <Util.h>
#include <Dice.h>
using namespace std;

void testInteger() {
	Random rng;
	cout << "1.) Test Integer\n";
	long long int a = rng.nextInt();
	long long int b = rng.nextInt();
	cout << "- Ta lay ngau nhien 2 so, do la: " << a << ", " << b << endl;
	cout << "- UCLN cua " << a << " va " << b << " la: " << Integer::gcd(a, b) << endl << endl;
}

void testRandom() {
	Random rng;
	cout << "2.) Test Random\n";
	int a = rng.nextInt();
	int b = rng.nextInt();
	
	if (a > b) {
		int temp = a;
		a = b;
		b = temp;
	}

	cout << "- Ta lay ngau nhien 2 so, do la: " << a << ", " << b << endl;
	cout << "- Ta lay ngau nhien 1 so trong khoang (" << a << "; " << b << "), do la: " << rng.nextInt(a, b) << endl;
	cout << "- Ta lay ngau nhien 1 so trong khoang (" << 0 << "; " << b - 1 << "), do la: " << rng.nextInt(b) << endl << endl;

};
void testDice() {
	Random rng;
	Dice dice;
	int n = rng.nextInt(50);
	cout << "3.) Test Dice\n";
	cout << "- Sau " << n << " lan gieo xuc xac, ta duoc lan luot so diem la:\n";
	for (int i = 0; i < n; ++i) {
		cout << dice.roll() << " ";
	}
	cout << endl << endl;
};

void testUtil() {
	Random rng;
	vector<int>arr;
	int n = rng.nextInt(50);
	cout << "4.) Test Util\n";
	cout << "- Trong Util chi chua 1 ham printArray\n";
	cout << "\t+ Tao 1 array co " << n << " phan tu ngau nhien, array do la:\n";
	for (int i = 0; i < n; ++i) {
		arr.push_back(rng.nextInt());
	}
	Util::printArray(arr);
	cout << endl << endl;
};

void testDynamicArray() {
	Random rng;
	DynamicArray<int>arr;
	cout << "5.) Test Dynamic Array\n";
	int n = rng.nextInt(50);
	cout << "\t+ Tao 1 dynamic array co " << n << " phan tu ngau nhien, array do la:\n";
	for (int i = 0; i < n; ++i) {
		arr.push_back(rng.nextInt());
	}
	cout << arr << endl;
}

class box {
private:
	int x, y, z;
public:
	box(){
		x = y = z = 0;
	}
	box(int _x, int _y, int _z) {
		x = _x;
		y = _y;
		z = _z;
	}
	~box() {}
	void printBox() {
		cout << x << " " << y << " " << z << endl;
	}

};

class biggerBox {
private:
	box BOX;
	int gooloo;
public:
	biggerBox() {
		//do nothing
	}
	biggerBox(const box& _box, const int& _gooloo) {
		BOX = _box;
		gooloo = _gooloo;
	}
	~biggerBox() {}
	void printBox() {
		BOX.printBox();
		cout << gooloo << endl;
	}
};

biggerBox initBox() {
	box BOX(1, 2, 3);
	biggerBox test(BOX, 4);
	return test;
}

int main() {
	/*
	testInteger();
	testRandom();
	testDice();
	testUtil();
	testDynamicArray();
	*/

	int i = 0;
	cout << ++i << endl;
	cout << " " << i++ << endl;
	return 0;
}