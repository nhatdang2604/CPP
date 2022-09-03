#include <iostream>
using namespace std;

void khoiTao(double **p) {
	for (int i = 0; i < 5; ++i) {
		*(p + i) = new double[i + 1];
	}
}

void thuHoi(double **p) {
	for (int i = 3; i <= 7; ++i) {
		delete[]p[i];
	}
	delete[]p;
}

void main() {
	double *p[10];
	khoiTao(p + 3);
	thuHoi(p);
}