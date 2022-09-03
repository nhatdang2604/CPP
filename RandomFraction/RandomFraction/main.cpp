#include "Fraction.h"

#include <time.h>
#include <vector>
using namespace std;

#define LOWER_BOUND 5
#define UPPER_BOUND 20

vector<Fraction> randomizeFractions() {
	srand(unsigned int(time(NULL)));
	int n = rand() % (UPPER_BOUND - LOWER_BOUND + 1) + LOWER_BOUND;
	vector<Fraction> result(n);
	for (int i = 0; i < n; ++i) {
		result[i].setNumerator(rand());

		//Denominator must be different from 0
		do {
			result[i].setDenominator(rand());
		} while (result[i].denominator() == 0);
	}
	return result;
}

Fraction addAllFraction(vector<Fraction>& fractions) {
	Fraction result;
	for (unsigned int i = 0; i < fractions.size(); ++i) {
		result = result + fractions[i];
		result.reduce();
	}
	return result;
}

void testRandomizeFractions(vector<Fraction>& fractions) {
	fractions = randomizeFractions();
	cout << "- Co tong cong " << fractions.size() << " phan so duoc tao ra\n";
	cout << "- Cac phan so lan luot la:\n";
	for (unsigned int i = 0; i < fractions.size(); ++i) {
		cout << "\t+ Phan so " << i << ": ";
		fractions[i].print();
		cout << endl;
	}
}

void testAddAllFractions(vector<Fraction>& fractions) {
	Fraction result = addAllFraction(fractions);
	cout << "- Tong cua cac phan so nay co gia tri la: ";
	result.print();
	cout << endl;
}

int main() {
	vector<Fraction> fractions;
	testRandomizeFractions(fractions);
	testAddAllFractions(fractions);
	system("PAUSE");
	return 0;
}