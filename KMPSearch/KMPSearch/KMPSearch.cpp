#include <iostream>
#include <string.h>
using namespace std;

#define MAX_CHARACTER 255

void input(char s[], int &lengthS) {
	cin.getline(s, MAX_CHARACTER);
	lengthS = strlen(s);
}

void LPSGenerator(char t[], int lengthT, int lps[]) {
	int pivot = 0;
	lps[0] = 0;
	for (int i = 1; i < lengthT; ++i) {
		if (t[pivot] == t[i]) {
			lps[i] = lps[i - 1] + 1;
			++pivot;
		}
		else {
			pivot = 0;
			if (t[pivot] == t[i]) ++pivot;
			lps[i] = pivot;
		}
	}
}


int KMPSearching(char s[], char t[], int lengthS, int lengthT) {
	int lps[MAX_CHARACTER];

	//Tim LPS cua xau t (xau can tim)
	LPSGenerator(t, lengthT, lps);

	int pivot = 0;
	for (int i = 0; i < lengthS; ++i) {
		if (s[i] == t[pivot]) {
			++pivot;

			//Sau khi da xet qua phan tu cuoi cung cua chuoi can tim
			if (pivot == lengthT) return i - lengthT + 1;
		}
		else {			
			if (pivot > 0) {

				//pivot se la vi tri tien to cua S, sau do + 1;
				pivot = lps[pivot - 1];

				//Giu i lai, khong cho ++i, de tiep tuc so sanh s[pivot] moi va s[i] cu
				--i;

				// Neu pivot = 0 (pivot khong bao gio am),
				// Tiep tuc qua trinh ++i (Khong giu lai),
				// pivot giu nguyen, pivot = 0
			}
		}
	}
	return -1;
}

int main() {
	char s[MAX_CHARACTER], t[MAX_CHARACTER];
	int lengthS = 0, lengthT = 0;
	cout << "Moi ban nhap xau goc: ";
	input(s, lengthS);
	cout << "Moi ban nhap xau can tim: ";
	input(t, lengthT);
	int result = KMPSearching(s, t, lengthS, lengthT);
	if (result != -1) {
		cout << "Xau " << t << " xuat hien o vi tri thu "
			<< result << " (Tinh tu vi tri 0)\n";
	}
	else {
		cout << "Khong tim thay !\n";
	}
	return 0;
}