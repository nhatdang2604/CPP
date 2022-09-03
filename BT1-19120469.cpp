// BT1-19120469.cpp : Defines the entry point for the console application.
//


#define _CRT_SECURE_NO_WARNINGS

#include <math.h>
#include <stdio.h>

#define MAX_TREE 1000
#define NUMBER_OF_TYPE 3
#define EPSILON 0.00001 // epsilon la 1 con so rat nho (epsilon ~ 0)

using namespace std;

//---------------------------------------------------------------------

struct point {
	double x, y;
};

struct tree {
	point positsion;
	int type;	//0 - Cao su, 1 - Ca phe, 2 - Che
};

struct fence {
	point topRight, bottomLeft; // Hinh chu nhat co dinh bang 2 duong cheo
};

struct farm {
	tree trees[MAX_TREE];
	int numberOfTree;
	int numberOfTreeEachType[NUMBER_OF_TYPE] = { 0, 0, 0 };
};


//---------------------------------------------------------------------

void input(farm &nongTrai, double &average_x, double &average_y) {
	freopen("NongTrai.in", "r+", stdin);
	scanf("%d", &nongTrai.numberOfTree);
	for (int i = 0; i < nongTrai.numberOfTree; ++i) {
		scanf("%lf %lf %d", &nongTrai.trees[i].positsion.x, &nongTrai.trees[i].positsion.y, &nongTrai.trees[i].type);
		average_x += nongTrai.trees[i].positsion.x;
		average_y += nongTrai.trees[i].positsion.y;
	}
	average_x /= nongTrai.numberOfTree; //tinh trung binh cong toa do x,y cua tat ca cac cay
	average_y /= nongTrai.numberOfTree;
}

void countTreeOfEachType(farm &nongTrai) {
	for (int i = 0; i < nongTrai.numberOfTree; ++i) {
		++nongTrai.numberOfTreeEachType[nongTrai.trees[i].type];
	}
}

double fencePerimeter(farm nongTrai, fence &hangRao) {
	double x_max = nongTrai.trees[0].positsion.x,
		   x_min = nongTrai.trees[0].positsion.x,
		   y_max = nongTrai.trees[0].positsion.y,
		   y_min = nongTrai.trees[0].positsion.y;
	for (int i = 1; i < nongTrai.numberOfTree; ++i) { //Tim x_max, x_min, y_max, y_min cua tat ca cay trong nong trai
		if (x_max < nongTrai.trees[i].positsion.x) x_max = nongTrai.trees[i].positsion.x;
		if (x_min > nongTrai.trees[i].positsion.x) x_min = nongTrai.trees[i].positsion.x;
		if (y_max < nongTrai.trees[i].positsion.y) y_max = nongTrai.trees[i].positsion.y;
		if (y_min > nongTrai.trees[i].positsion.y) y_min = nongTrai.trees[i].positsion.y;
	}
	hangRao.topRight.x = x_max;
	hangRao.topRight.y = y_max;
	hangRao.bottomLeft.x = x_min;
	hangRao.bottomLeft.y = y_min;
	return 2 * ((x_max - x_min) + (y_max - y_min)); //khong can xet am/duong, vi x_max >= x_min, y_max >= y_min
}

double EuclidDistance(point A, point B) {
	return sqrt((A.x - B.x)*(A.x - B.x) + (A.y - B.y)*(A.y - B.y));
}

double theShortestLength(farm nongTrai, fence hangRao, double average_x, double average_y) { // Su dung thuat toan Weiszfeld
	double numerator_x, numerator_y, denominator, distance, result = 0;
	int limit; 
	point plumbPositsion; // Vi tri dat may bom
	plumbPositsion.x = average_x; // Vi tri dau tien x0, y0 trong Weiszfeld la vi tri Trung Binh Cong;
	plumbPositsion.y = average_y; 
	(nongTrai.numberOfTree < 100) ? limit = 100 : limit = nongTrai.numberOfTree; // cai thien do chinh xac khi so luong cay qua nho ( nongTrai.numberOfTree < 100 )
	for (int i = 0; i < limit; ++i) {  // thuat toan Weiszfeld
		numerator_x = 0; numerator_y = 0; denominator = 0;
		for (int j = 0; j < nongTrai.numberOfTree; ++j) {
			distance = EuclidDistance(plumbPositsion, nongTrai.trees[j].positsion);
			if (distance == 0) distance += EPSILON;  // + epsilon de tranh truong hop chia cho 0 (truong hop cap nhat diem bi trung trong Weiszfeld);
			numerator_x += nongTrai.trees[j].positsion.x / distance; // cong thuc cua Weiszfeld
			numerator_y += nongTrai.trees[j].positsion.y / distance;
			denominator+= 1 / distance;
		}
		plumbPositsion.x = numerator_x / denominator; 
		plumbPositsion.y = numerator_y / denominator;	// cap nhat lai toa do (x,y) de dat may bom
	}
	if ((plumbPositsion.x > hangRao.topRight.x) || (plumbPositsion.y > hangRao.topRight.y) 
	 || (plumbPositsion.x < hangRao.bottomLeft.x) || (plumbPositsion.y < hangRao.bottomLeft.y)) { //Neu vi tri dat may bom nam ngoai Hang Rao
		plumbPositsion.x = average_x; // Ta dat lai may bom o vi tri Trung Binh Cong (Luon luon nam trong Hang Rao) (do chinh xac thap!) 
		plumbPositsion.y = average_y; 	
	}
	for (int i = 0; i < nongTrai.numberOfTree; ++i) {
		result += EuclidDistance(plumbPositsion, nongTrai.trees[i].positsion); // tinh tong chieu dai ong nuoc 
	}
	return result;
}

void output(farm NongTrai, double perimeter, double plumbLength) {
	FILE *outfile;
	freopen("NongTrai.out", "w+", stdout);
	for (int i = 0; i < 3; ++i) {
		printf("%d ", NongTrai.numberOfTreeEachType[i]);
	}
	printf("\n%.2lf\n%.2lf", perimeter, plumbLength);
}

int main()
{
	farm NongTrai;
	fence HangRao;
	double average_x = 0, average_y = 0; //trung binh cong toa do x, y cua tat ca cac cay
	input(NongTrai, average_x, average_y);
	countTreeOfEachType(NongTrai);
	double perimeter = fencePerimeter(NongTrai, HangRao);
	double plumbLength = theShortestLength(NongTrai, HangRao, average_x, average_y);
	output(NongTrai, perimeter, plumbLength);
	return 0;
}

