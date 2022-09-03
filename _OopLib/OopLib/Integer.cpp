#include "Integer.h"

long long int Integer::gcd(long long int a,long long int b) {
	long long int temp;
	while (b != 0) {
		temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}