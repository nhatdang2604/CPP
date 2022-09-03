#include "DonThuc.h"

//construction
DonThuc::DonThuc() {
	m_heSo = m_soMu = 0;
};
DonThuc::DonThuc(int heSo, int soMu) {
	m_heSo = heSo;
	m_soMu = soMu;
};
DonThuc::DonThuc(const DonThuc& a) {
	m_heSo = a.m_heSo;
	m_soMu = a.m_soMu;
};

//tinh toan
double DonThuc::cal(int x) {
	return m_heSo*pow(x, m_soMu);
}

//dao ham
DonThuc DonThuc::diff() {
	return DonThuc(m_heSo*m_soMu, m_soMu - 1);
}

//xuat
void DonThuc::output() {
	if (this->m_heSo != 0) {
		if (this->m_heSo != 1) cout << m_heSo;
		if (this->m_soMu != 0) cout << "x";
		if (this->m_soMu != 1 && this->m_soMu != 0) cout << "^" << m_soMu;
	}
	cout << endl;
}

//cong
void DonThuc::sum(DonThuc g) {
	if (this->m_soMu == g.m_soMu) {
		DonThuc temp(this->m_heSo + g.m_heSo, this->m_soMu);
		temp.output();
	}
	else {
		cout << "Khong cung bac! \n";
		system("pause");
	}
}

//nhan
void DonThuc::multiply(DonThuc g) {
	DonThuc temp(this->m_heSo*g.m_heSo, this->m_soMu + g.m_soMu);
	temp.output();
}

