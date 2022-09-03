#include"Dice.h"
#include<vector>
using namespace std;

#define LOWER_BOUND 5
#define UPPER_BOUND 20

vector<int> calcPoints(Dice& dice, Random& rng) {
	int n = rng.nextInt(LOWER_BOUND, UPPER_BOUND);
	vector<int> points(n);
	for (int i = 0; i < n; ++i)
		points[i] = dice.roll();
	return points;
}

int calcTotalPoint(const vector<int>& points) {
	int result = 0;
	for (unsigned int i = 0; i < points.size(); ++i)
		result += points[i];
	return result;
}

double calcAveragePoint(const vector<int>& points) {
	double result = (double)calcTotalPoint(points);
	result /= double(points.size());
	return result;
}

void printPoints(const vector<int>& points) {
	cout << "- So luong lan gieo la: " << points.size() << endl;
	cout << "- Cac lan gieo lan luot duoc so diem la:\n\n";
	for (unsigned int i = 0; i < points.size(); ++i) {
		cout << "\t+ Lan " << i + 1 << ": " << points[i] << " diem\n";
	}
	cout << endl;
}

void printTotal(const vector<int>& points) {
	cout << "- Tong so diem gieo duoc la: " << calcTotalPoint(points) << endl;
}

void printAverage(const vector<int>& points) {
	cout << "- So diem trung binh gieo duoc la: " << calcAveragePoint(points) << endl;
}
int main() {
	Dice dice;
	Random rng;
	vector<int> points = calcPoints(dice, rng);
	printPoints(points);
	printTotal(points);
	printAverage(points);
	system("PAUSE");
	return 0;
}
