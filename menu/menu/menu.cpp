// 19120082.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <malloc.h>
#include <iostream>
using namespace std;

struct phanso
{
	int tu;
	int mau;
};

phanso* ps = NULL;
int n;

void nhapSoLuong(int& n)
{
	bool Tcin;
	cout << "Moi thay nhap so luong phan so (n>0): ";
	do
	{
		cin >> n;
		Tcin = cin.fail();
		system("cls");
		if (Tcin || n <= 0)
		{
			cout << "Thay da nhap sai, moi thay nhap lai: ";
			cin.clear();
			cin.ignore();
		}
	} while (Tcin || n <= 0);
}

void nhap1ps(phanso* ps)
{
	bool Tcin;
	cout << "Moi thay nhap tu so: ";
	do
	{
		cin >> ps->tu;
		Tcin = cin.fail();
		if (Tcin)
		{
			cout << "Thay da nhap sai, moi thay nhap lai tu so: ";
			cin.clear();
			cin.ignore();
		}
	} while (Tcin);
	cout << "Moi thay nhap mau so (khac 0): ";
	do
	{
		cin >> ps->mau;
		Tcin = cin.fail();
		if (Tcin || ps->mau == 0)
		{
			cout << "Thay da nhap sai, moi thay nhap lai mau so: ";
			cin.clear();
			cin.ignore();
		}
	} while (Tcin || ps->mau == 0);
	cout << "--------------------" << endl;
}

void nhapMangPhanSo(phanso*& ps, int& n)
{
	cout << "Day la chuc nang nhap mang phan so." << endl;
	nhapSoLuong(n);
	ps = (phanso*)malloc(n * sizeof(phanso));
	for (int i = 0; i < n; i++)
	{
		cout << "Moi thay nhap phan so thu " << i + 1 << ":" << endl;
		nhap1ps(ps + i);
	}
}

void xuat1ps(phanso* ps)
{
	if (ps->tu != 0)
	{
		cout << ps->tu << "/" << ps->mau << endl;
	}
	else
	{
		cout << ps->tu << endl;
	}
}

void xuatMangPhanSo(phanso* ps, int n)
{
	cout << "Day la chuc nang xuat mang phan so." << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "Phan so thu " << i + 1 << ": ";
		xuat1ps(ps + i);
	}
}

void chenPhanSo(phanso*& ps, int& n, phanso x)
{
	int m = n + 1;
	phanso* psnew = (phanso*)realloc(ps, m * sizeof(phanso));
	if (psnew != NULL)
	{
		*(psnew + n) = x;
		n++;
		ps = psnew;
		cout << "Da chen thanh cong phan so vao cuoi mang." << endl;
	}
	else
	{
		cout << "Chen khong thanh cong." << endl;
	}
}

void xoaPhanSo(phanso*& ps, int& n)
{
	int m = n - 1;
	phanso* psnew = (phanso*)realloc(ps, m * sizeof(phanso));
	if (psnew != NULL)
	{
		n--;
		ps = psnew;
		cout << "Da xoa thanh cong phan so o cuoi mang." << endl;
	}
	else
	{
		cout << "Xoa khong thanh cong." << endl;
	}
}

void huyMangPhanSo(phanso*& ps)
{
	free(ps);
}

int Menu()
{
	system("cls");
	cout << "MAIN MENU" << endl;
	cout << "---------" << endl;
	cout << "1.Xuat mang phan so da nhap ra man hinh." << endl;
	cout << "2.Chen them 1 phan so vao cuoi mang." << endl;
	cout << "3.Xoa 1 phan so o cuoi mang." << endl;
	cout << "4.Xoa mang phan so va nhap lai mang moi." << endl;
	cout << "5.Xoa mang phan so va thoat chuong trinh." << endl;
	return 5;
}

int SelectMenu(int SoLuaChon)
{
	int lenh;
	bool Tcin;
	cout << "Moi thay chon chuc nang thuc hien: ";
	do
	{
		cin >> lenh;
		Tcin = cin.fail();
		if (Tcin || lenh<1 || lenh>SoLuaChon)
		{
			cout << "Thay da nhap sai, moi thay nhap lai: ";
			cin.clear();
			cin.ignore();
		}
	} while (Tcin || lenh<1 || lenh>SoLuaChon);
	return lenh;
}

void runMenu(int lenh)
{
	if (lenh == 5)
	{
		huyMangPhanSo(ps);
		return;
	}
	system("cls");
	switch (lenh)
	{
	case 1:
		cout << "1.Xuat mang phan so da nhap ra man hinh." << endl;
		cout << "-------------------------------------------------" << endl;
		xuatMangPhanSo(ps, n);
		system("pause");
		break;
	case 2:
		cout << "2.Chen them 1 phan so vao cuoi mang." << endl;
		cout << "-------------------------------------------------" << endl;
		phanso psnew;
		bool Tcin;
		cout << "Moi thay nhap phan so muon chen:" << endl;
		cout << "Moi thay nhap tu so: ";
		do
		{
			cin >> psnew.tu;
			Tcin = cin.fail();
			if (Tcin)
			{
				cout << "Thay da nhap sai, moi thay nhap lai tu so: ";
				cin.clear();
				cin.ignore();
			}
		} while (Tcin);
		cout << "Moi thay nhap mau so (khac 0): ";
		do
		{
			cin >> psnew.mau;
			Tcin = cin.fail();
			if (Tcin || psnew.mau == 0)
			{
				cout << "Thay da nhap sai, moi thay nhap lai mau so: ";
				cin.clear();
				cin.ignore();
			}
		} while (Tcin || psnew.mau == 0);
		chenPhanSo(ps, n, psnew);
		system("pause");
		break;
	case 3:
		cout << "3.Xoa 1 phan so o cuoi mang." << endl;
		cout << "-------------------------------------------------" << endl;
		xoaPhanSo(ps, n);
		system("pause");
		break;
	case 4:
		cout << "4.Xoa mang phan so va nhap lai mang moi." << endl;
		cout << "-------------------------------------------------" << endl;
		huyMangPhanSo(ps);
		nhapMangPhanSo(ps, n);
		system("pause");
		break;
	}
}

int main()
{
	nhapMangPhanSo(ps, n);
	int Lenh;
	do
	{
		Lenh = SelectMenu(Menu());
		runMenu(Lenh);
	} while (Lenh != 5);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
