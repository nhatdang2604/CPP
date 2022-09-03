#include<iostream>
#include<vector>
#include<string>
using namespace std;

#define UNCONVERTED 128
#define LOWER_BOUND -128
#define UPPER_BOUND 127
#define PADDING_SIZE 8
#define BIN 2
#define DUMMY false


int convertBinToDec(const vector<bool>& value) {
	if (value.size() > 8 || value.size() < 1) return UNCONVERTED;
	int result = 0;
	int coefficient = 1;
	for (int i = PADDING_SIZE - 1; i > 0; --i) {
		result += int(value[i]) * coefficient;
		coefficient *= BIN;
	}

	result += -1 * int(value[0]) * coefficient;
	return result;
}

bool halfAdder(const bool& firstOperand, const bool& secondOperand, bool& carry) {
	carry = firstOperand & secondOperand;
	return firstOperand ^ secondOperand;
}

bool fullAdder(const bool& firstOperand, const bool& secondOperand, const bool& thirdOperand, bool& carry) {
	bool carry1 = DUMMY;
	bool carry2 = DUMMY;
	bool sum1 = halfAdder(firstOperand, secondOperand, carry1);
	bool sum = halfAdder(sum1, thirdOperand, carry2);
	carry = carry1 | carry2;
	return sum;
}


vector<bool> operator + (const vector<bool>& firstOperand, const vector<bool>& secondOperand) {
	vector<bool> result(firstOperand.size());
	bool * carry = new bool[firstOperand.size() - 1];
	bool dummy = DUMMY;
	memset(carry, DUMMY, (firstOperand.size() - 2) * sizeof(bool));

	result[firstOperand.size() - 1] = halfAdder(firstOperand[firstOperand.size() - 1], secondOperand[firstOperand.size() - 1], carry[firstOperand.size() - 2]);
	for (int i = firstOperand.size() - 2; i > 0; --i) {
		result[i] = fullAdder(firstOperand[i], secondOperand[i], carry[i], carry[i - 1]);
	}
	result[0] = fullAdder(firstOperand[0], secondOperand[0], carry[0], dummy);
	delete[] carry;
	return result;
}

vector<bool> negative(const vector<bool>& value) {
	//result = ~result
	vector<bool> result(value.size());
	vector<bool> one(value.size(), false);
	one[value.size() - 1] = true;
	for (unsigned int i = 0; i < value.size(); ++i) {
		result[i] = !value[i];
	}

	//result = result + 1

	result = result + one;
	return result;
}


vector<bool> operator -(const vector<bool>& firstOperand, const vector<bool>& secondOperand) {
	vector<bool> negativeSecondOperand = negative(secondOperand);
	vector<bool> result = firstOperand + negativeSecondOperand;
	return result;
}

vector<bool> operator << (const vector<bool>& firstOperand, const int& secondOperand) {
	vector<bool> rawResult(firstOperand.size() + secondOperand, false);
	for (unsigned int i = 0; i < firstOperand.size(); ++i) {
		rawResult[i] = firstOperand[i];
	}
	vector<bool> result(rawResult.begin() + secondOperand, rawResult.end());
	return result;
}

vector<bool> operator >> (const vector<bool>& firstOperand, const int& secondOperand) {

	vector<bool> rawResult(firstOperand.size() + secondOperand, false);
	for (unsigned int i = 0; i < firstOperand.size(); ++i) {
		rawResult[i + secondOperand] = firstOperand[i];
	}
	vector<bool> result(rawResult.begin(), rawResult.begin() + firstOperand.size());
	return result;
}

/*Using Booth algorithm
Only use for: 4bits x 4bitx ([-8; 7] x [-8; 7])*/
vector<bool> operator *(const vector<bool>& firstOperand, const vector<bool>& secondOperand) {
	
	vector<bool> A(PADDING_SIZE - 4, false);
	vector<bool> Q(firstOperand.begin() + 4, firstOperand.end());
	vector<bool> M(secondOperand.begin() + 4, secondOperand.end());
	bool QMinus = false;
	
	//Initialize
	vector<bool> rawResult(PADDING_SIZE + 1);
	for (int i = 0; i < PADDING_SIZE - 4; ++i) rawResult[i] = A[i];
	for (int i = PADDING_SIZE - 4; i < PADDING_SIZE; ++i) rawResult[i] = Q[i - (PADDING_SIZE - 4)];
	rawResult[PADDING_SIZE] = QMinus;

	for (int i = 0; i < PADDING_SIZE - 4; ++i) {
		if (rawResult[PADDING_SIZE - 1] && !rawResult[PADDING_SIZE]) {
			A = A - M;
			for (int i = 0; i < PADDING_SIZE - 4; ++i) rawResult[i] = A[i];
			for (int i = PADDING_SIZE - 4; i < PADDING_SIZE; ++i) rawResult[i] = Q[i - (PADDING_SIZE - 4)];
			rawResult[PADDING_SIZE] = QMinus;
		}
		else {
			if (!rawResult[PADDING_SIZE - 1] && rawResult[PADDING_SIZE]) {
				A = A + M;
				for (int i = 0; i < PADDING_SIZE - 4; ++i) rawResult[i] = A[i];
				for (int i = PADDING_SIZE - 4; i < PADDING_SIZE; ++i) rawResult[i] = Q[i - (PADDING_SIZE - 4)];
				rawResult[PADDING_SIZE] = QMinus;
			}
		}

		//Dich phai SO HOC
		rawResult = rawResult >> 1;
		rawResult[0] = A[0];

		for (int i = 0; i < PADDING_SIZE - 4; ++i) A[i] = rawResult[i];
		for (int i = PADDING_SIZE - 4; i < PADDING_SIZE; ++i) Q[i - (PADDING_SIZE - 4)] = rawResult[i];
		QMinus = rawResult[PADDING_SIZE];
	}
	vector<bool> result(rawResult.begin(), rawResult.end() - 1);
	return result;
}


vector<bool> operator /(const vector<bool>& numerator, const vector<bool>& denominator) {
	vector<bool> A(PADDING_SIZE, false);
	vector<bool> Q(numerator);
	vector<bool> M(denominator);
	if (numerator[0]) {Q = negative(Q);}
	if (denominator[0]) { M = negative(M);}

	vector<bool> rawResult(2 * PADDING_SIZE);
	for (int i = 0; i < PADDING_SIZE; ++i) rawResult[i] = A[i];
	for (int i = PADDING_SIZE; i < 2 * PADDING_SIZE; ++i) rawResult[i] = Q[i - PADDING_SIZE];

	for (int i = 0; i < PADDING_SIZE; ++i) {
		rawResult = rawResult << 1;
		
		for (int i = 0; i < PADDING_SIZE; ++i) A[i] = rawResult[i];
		for (int i = PADDING_SIZE; i < 2 * PADDING_SIZE; ++i) Q[i - PADDING_SIZE] = rawResult[i];
		A = A - M;
		if (A[0]) {
			Q[PADDING_SIZE - 1] = false;
			A = A + M;
		}
		else {
			Q[PADDING_SIZE - 1] = true;
		}

		for (int i = 0; i < PADDING_SIZE; ++i) rawResult[i] = A[i];
		for (int i = PADDING_SIZE; i < 2 * PADDING_SIZE; ++i) rawResult[i] = Q[i - PADDING_SIZE];
	}

	vector<bool> result(rawResult.begin() + PADDING_SIZE, rawResult.end());

	//(A, Q) khac dau voi M => result chua BU 2 cua thuong
	//(A, Q) cung dau voi M => result chua thuong
	if (numerator[0] ^ denominator[0]) {
		result = negative(result);
	}

	return result;
}

vector<bool> convertDecToBin(const int& value) {
	
	vector<bool> result;
	if (value < LOWER_BOUND || value > UPPER_BOUND) return result;
	int dummy; 

	//if value is negative number => we have to convert its positive form first
	value < 0 ? dummy = -value : dummy = value;
	while (dummy > 0) {
		result.push_back(dummy%BIN);
		dummy /= BIN;
	}

	int padding = PADDING_SIZE - result.size();
	for (int i = 0; i < padding; ++i) {
		result.push_back(false);
	}
	reverse(result.begin(), result.end());

	//If value is negative number
	if (value < 0) {
		result = negative(result);
	}

	return result;
}

ostream& operator << (ostream& device, const vector<bool>& binary) {
	if (binary.size() == PADDING_SIZE) {
		for (int i = 0; i < PADDING_SIZE; ++i) {
			device << binary[i];
		}
	}
	else {
		device << "So nhi phan khong hop le!";
	}
	return device;
}

void convertDecToBinTest() {
	int n;
	cout << "1.) Chuyen tu thap phan sang nhi phan (bu 2 - 8 bits)\n";
	cout << "Moi thay nhap 1 so nguyen, nam trong khoang [-128, 127]: ";
	cin >> n;
	cout << "Dang nhi phan (bu 2 - 8 bits) cua " << n << " la: " << convertDecToBin(n) << endl;
	cout << endl;
	cin.ignore();
}

void convertBinToDecTest() {
	string buffer;
	cout << "2.) Chuyen tu nhi phan sang thap phan (bu 2 - 8 bits)\n";
	cout << "Moi thay nhap 1 day nhi phan (chi co 0 va 1), khong co dau cach, do dai la 8 bits:";
	getline(cin, buffer);
	vector<bool> n(PADDING_SIZE);
	for (int i = 0; i < PADDING_SIZE; ++i) {
		n[i] = bool(buffer[i] - '0');
	}
 	cout << "Dang thap phan cua " << n << " la: " << convertBinToDec(n) << endl;
	cout << endl;
}
 
void addTest() {
	cout << "3.) Thuc hien phep cong (bu 2 - 8 bits)\n";
	int n, m;
	cout << "Moi thay nhap 2 so nguyen, nam trong khoang [-128; 127]: ";
	cin >> n >> m;
	vector<bool> nBin = convertDecToBin(n);
	vector<bool> mBin = convertDecToBin(m);
	vector<bool> result = nBin + mBin;
	cout << " " << nBin << endl;
	cout << "+" << endl;
	cout << " " << mBin << endl;
	cout << "----------" << endl;
	cout << " " << result << endl;
	cout <<"= " << convertBinToDec(result) << endl;
	cout << endl;
}

void subtractTest() {
	cout << "4.) Thuc hien phep tru (bu 2 - 8 bits)\n";
	int n, m;
	cout << "Moi thay nhap 2 so nguyen, nam trong khoang [-128; 127]: ";
	cin >> n >> m;
	vector<bool> nBin = convertDecToBin(n);
	vector<bool> mBin = convertDecToBin(m);
	vector<bool> result = nBin - mBin;
	cout << " " << nBin << endl;
	cout << "-" << endl;
	cout << " " << mBin << endl;
	cout << "----------" << endl;
	cout << " " << result << endl;
	cout << "= " << convertBinToDec(result) << endl;
	cout << endl;
}

void multiTest() {
	cout << "5.) Thuc hien phep nhan co dau (bu 2 - 8 bits, su dung thuat toan Booth)\n";
	int n, m;
	cout << "Moi thay nhap 2 so nguyen, nam trong khoang [-8; 7]: ";
	cin >> n >> m;
	vector<bool> nBin = convertDecToBin(n);
	vector<bool> mBin = convertDecToBin(m);
	vector<bool> result = nBin * mBin;
	cout << "    ";
	for (int i = 0; i < 4; ++i) cout << nBin[4 + i];
	cout << endl;
	cout << "*" << endl;
	cout << "    ";
	for (int i = 0; i < 4; ++i) cout << mBin[4 + i];
	cout << endl;
	cout << "----------" << endl;
	cout << " " << result << endl;
	cout << "= " << convertBinToDec(result) << endl;
	cout << endl;
}

void divideTest() {
	cout << "6.) Thuc hien phep chia co dau (bu 2 - 8 bits)\n";
	int n, m;
	cout << "Moi thay nhap 2 so nguyen, nam trong khoang [-128; 127]: ";
	cin >> n >> m;
	vector<bool> nBin = convertDecToBin(n);
	vector<bool> mBin = convertDecToBin(m);
	vector<bool> result = nBin / mBin;
	cout << " " << nBin << endl;
	cout << "/" << endl;
	cout << " " << mBin << endl;
	cout << "----------" << endl;
	cout << " " << result << endl;
	cout << "= " << convertBinToDec(result) << endl;
	cout << endl;
}

int main() {
	convertDecToBinTest();
	convertBinToDecTest();
	addTest();
	subtractTest();
	multiTest();
	divideTest();
	system("PAUSE");
	return 0;
}