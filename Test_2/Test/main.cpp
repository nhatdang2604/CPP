#include <iostream>
#include "Random.h"
using namespace std;

int main() {
	Random rng;
	cout << rng.nextInt(3, 4) << endl;

	return 0;
}