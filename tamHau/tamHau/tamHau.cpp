// tamHau.cpp : Defines the entry point for the console application.
//

#include <iostream>
using namespace std;
int chessboard[8][8];

#define QUEEN_NUMBERS 8

void printChessboard(int counter) {
	
	cout << "********************************\n\n";
	cout << "Loi giai thu " << counter << ": \n\n";
	for (int i = 0; i < QUEEN_NUMBERS; ++i) {
		for (int j = 0; j < QUEEN_NUMBERS; ++j) {
			cout << chessboard[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void Try(int row, bool checkCol[], bool checkFowardDiagonal[], bool checkBackwardDiagonal[], int &counter) {
	for (int j = 0; j < QUEEN_NUMBERS; ++j) {
		if (checkCol[j] && checkFowardDiagonal[row + j] && checkBackwardDiagonal[row - j + QUEEN_NUMBERS - 1]) {
			chessboard[row][j] = 1;
			if (row == QUEEN_NUMBERS - 1) {
				++counter;
				printChessboard(counter);
				chessboard[row][j] = 0;
			}
			else {
				checkCol[j] = false;
				checkFowardDiagonal[row + j] = false;
				checkBackwardDiagonal[row - j + QUEEN_NUMBERS - 1] = false;
				Try(row + 1, checkCol, checkFowardDiagonal, checkBackwardDiagonal, counter);
				checkCol[j] = true;
				checkFowardDiagonal[row + j] = true;
				checkBackwardDiagonal[row - j + QUEEN_NUMBERS - 1] = true;
				chessboard[row][j] = 0;
			}
		}
	}
}

int main()
{
	bool checkCol[QUEEN_NUMBERS], checkFowardDiagonal[2 * QUEEN_NUMBERS - 1], checkBackwardDiagonal[2 * QUEEN_NUMBERS - 1];
	int counter = 0;
	cout << "Day la toan bo cac loi giai cua bai toan 8 quan hau!\n\n";
	cout << "Moi thay nhan enter de tiep tuc\n\n";
	system("pause");
	Try(0, checkCol, checkFowardDiagonal, checkBackwardDiagonal, counter);
	cout << "********************************\n\n";
	cout << "Nhung vi tri co so 1 chinh la vi tri dat quan hau!\n\n";
	return 0;
}

