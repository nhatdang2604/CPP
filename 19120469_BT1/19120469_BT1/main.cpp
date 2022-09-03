#include <iostream>
#include <string>
using namespace std;

#define BIN 2
#define OCT 8
#define DEC 10
#define HEX 16

int convertBinToDec(const string& value) {
	int result = 0;
	int coefficient = 1;
	for (int i = int(value.size()) - 1; i >= 0; --i) {
		result += int(value[i] - '0')*coefficient;
		coefficient *= BIN;
	}
	return result;
}

string convertDecToBin(const int& value) {
	if (value == 0) return "00000000";
	string result;
	int dummy = value;

	//Divide step
	while (dummy) {
		result.push_back(char(dummy%BIN + '0'));
		dummy /= BIN;
	}
	
	//Reverse the result
	reverse(result.begin(), result.end());
	return result;
}

int convertHexToDec(const string& value) {
	int result = 0;
	int coefficient = 1;
	for (int i = int(value.size()) - 1; i >= 0; --i) {
		if (value[i] >= '0' && value[i] <= '9') {
			result += int(value[i] - '0')*coefficient;
		}
		else {
			result += int(value[i] - 'A' + DEC)*coefficient;
		}
		coefficient *= HEX;
	}
	return result;
}

string convertDecToHex(const int& value) {
	if (value == 0) return "00000000";
	int digit;
	string result;
	int dummy = value;

	//Divide step
	while (dummy) {
		digit = dummy%HEX;
		digit < DEC ? result.push_back(char(digit + '0')) :
			result.push_back(char(digit - DEC + 'A'));

		dummy /= HEX;
	}

	//Reverse the result
	reverse(result.begin(), result.end());
	return result;
}

string convertBinToHex(const string& value) {
	int decValue = convertBinToDec(value);
	return convertDecToHex(decValue);
}

bool isHex(const string& value) {
	for (unsigned int i = 0; i < value.size(); ++i) {
		if (!(('0' <= value[i] && value[i] <= '9') || ('A' <= value[i] && value[i] <= 'F')))
			return false;
	}
	return true;
}

bool isBin(const string& value) {
	for (unsigned int i = 0; i < value.size(); ++i) {
		if (value[i] != '0' && value[i] != '1') {
			return false;
		}
	}
	return true;
}

void processDec() {
	int input;
	bool checkInput = false;
	cout << "Moi nhap 1 so Dec: ";
	cin >> input;
	if (input < 0) {
		cout << "Co loi! Khong the convert tu so am\n";
		return;
	}
	cout << "Cac dang cua " << input << " la:\n";
	cout << "- Bin: " << convertDecToBin(input) << endl;
	cout << "- Hex: " << convertDecToHex(input) << endl;
	cout << endl;
	cin.ignore(256, '\n');
	
}

void processHex() {
	string input;
	bool checkInput = false;
	cout << "Moi nhap 1 so Hex: ";
	getline(cin, input);
	if (!isHex(input)) {
		cout << "Khong hop le!\n";
		return;
	}
	cout << "Cac dang cua " << input << " la:\n";
	cout << "- Dec: " << convertHexToDec(input) << endl;
	cout << "- Bin: " << "Khong yeu cau" << endl;
	cout << endl;
}

void processBin() {
	string input;
	bool checkInput = false;
	cout << "Moi nhap 1 so Bin: ";
	getline(cin, input);
	if (!isBin(input)) {
		cout << "Khong hop le!\n";
		return;
	}
	cout << "Cac dang cua " << input << " la:\n";
	cout << "- Dec: " << convertBinToDec(input) << endl;
	cout << "- Hex: " << convertBinToHex(input) << endl;
	cout << endl;
}

int main() {
	processDec();
	processBin();
	processHex();
	system("PAUSE");
	return  0;
}