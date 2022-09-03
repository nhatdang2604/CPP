// maDiTuan.cpp : Defines the entry point for the console application.
//

#include <iostream>
using namespace std;

int chessboard[8][8];
//int X[8] = { 2,2,1,-1,-2,-2,-1,1 };
//int Y[8] = { 1,-1,-2,-2,-1,1,2,2 };

#define CHESSBOARD_SIZE 8
#define KNIGHT_STEP_NUMBERS 8

void input(int &x, int &y) {
	cout << "Moi thay nhap vi tri bat dau (x;y) cua quan ma (Reccommend chon (0;0)): \n\n";
	cout << "VD: Quan ma o vi bat dau la (0;0), nhap: 0 0\n\n";
	cout << "Moi thay nhap: ";
	cin >> x >> y;
	while (x < 0 || y < 0 || x >= CHESSBOARD_SIZE || y >= CHESSBOARD_SIZE) {
		cout << "Khong hop le! 0 <= x,y <= 7 !\n\n";
		cout << "Moi thay nhap lai vi tri bat dau: ";
		cin >> x >> y;
	}
	cout << "\n*****************************************\n\n";
	cout << "Khong phai luc nao cung co duoc ket qua, mot so truong hop mat rat nhieu thoi gian de ra ket qua! \n\n";
}

void printChessboard() {
	for (int i = 0; i < CHESSBOARD_SIZE; ++i) {
		for (int j = 0; j < CHESSBOARD_SIZE; ++j) {
			cout << chessboard[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

void Try(int x, int y, bool &checkLegit, int step) {
	if (!chessboard[x][y]) {
		chessboard[x][y] = step;
		if (step == CHESSBOARD_SIZE*CHESSBOARD_SIZE) {
			checkLegit = true;
			printChessboard();
			//chessboard[x][y] = 0;
			exit(0);
		}
		else {
			if (x - 2 >= 0 && y - 1 >= 0)							Try(x - 2, y - 1, checkLegit, step + 1);
			if (x - 2 >= 0 && y + 1 < CHESSBOARD_SIZE)				Try(x - 2, y + 1, checkLegit, step + 1);
			if (x - 1 >= 0 && y - 2 >= 0)							Try(x - 1, y - 2, checkLegit, step + 1);
			if (x - 1 >= 0 && y + 2 < CHESSBOARD_SIZE)				Try(x - 1, y + 2, checkLegit, step + 1);
			if (x + 1 < CHESSBOARD_SIZE && y - 2 >= 0)				Try(x + 1, y - 2, checkLegit, step + 1);
			if (x + 1 < CHESSBOARD_SIZE && y + 2 < CHESSBOARD_SIZE)	Try(x + 1, y + 2, checkLegit, step + 1);
			if (x + 2 < CHESSBOARD_SIZE && y - 1 >= 0)				Try(x + 2, y - 1, checkLegit, step + 1);
			if (x + 2 < CHESSBOARD_SIZE && y + 1 < CHESSBOARD_SIZE)	Try(x + 2, y + 1, checkLegit, step + 1);
			chessboard[x][y] = 0;
		}
	}
}

int main()
{
	int x = 0, y = 0;
	bool checkLegit = false;
	input(x, y);
	Try(x, y, checkLegit, 1);
	if (!checkLegit) cout << "\n*****************************************\n\n Khong co ket qua! \n\n";
	return 0;
}

