#pragma once
#include <iostream>
#include <math.h>
using namespace std;

class DonThuc {
private:
	int m_heSo;
	int m_soMu;
public:
	//construction
	DonThuc();
	DonThuc(int heSo, int soMu);
	DonThuc(const DonThuc& a);

	//tinh toan
	double cal(int x);

	//dao ham
	DonThuc diff();

	//xuat
	void output();

	//cong
	void sum(DonThuc g);

	//nhan
	void multiply(DonThuc g);

	//deconstruction
	~DonThuc() {};
};
