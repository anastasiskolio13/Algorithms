#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <set>
#include <cmath>
using namespace std;

struct point {
	int X;
	int Y;
	bool operator<(const point& other) const {
		return X > other.X || X == other.X && Y > other.Y;
	}
};

set<point> dominantPoints(set<point> S) {
	if (S.size() == 1)
		return S;
	int j = ceil((double)S.size() / 2);
	set<point> SL;
	set<point> SR;
	int i = 0;
	for (point p : S) {
		if (i < j)
			SL.insert(p);
		else
			SR.insert(p);
		++i;
	}
	set<point> DL = dominantPoints(SL);
	set<point> DR = dominantPoints(SR);
	auto it = DL.end();
	--it;
	int maxY = it->Y;
	for (auto it = DR.begin(); it != DR.end(); ) {
		if (maxY >= it->Y) 
			it = DR.erase(it); 
		else 
			++it;
	}
	set<point> D;
	for (point p : DL)
		D.insert(p);
	for (point p : DR)
		D.insert(p);
	return D;
}

void solveTestCase(int j) {
	string filenameOne = "in" + to_string(j) + ".txt";
	freopen(filenameOne.c_str(), "r", stdin);
	int N;
	scanf("%d", &N);
	set<point> S;
	for (int i = 0; i < N; ++i) {
		point p;
		scanf("%d %d", &p.X, &p.Y);
		S.insert(p);
	}
	set<point> D = dominantPoints(S);
	string filenameTwo = "out" + to_string(j) + ".txt";
	freopen(filenameTwo.c_str(), "r", stdin);
	int mySetSize = D.size();
	int correctSetSize;
	scanf("%d", &correctSetSize);
	if (mySetSize != correctSetSize) {
		printf("WA\n");
		return;
	}
	set<point> Q;
	for (int i = 0; i < correctSetSize; ++i) {
		point p;
		scanf("%d %d", &p.X, &p.Y);
		Q.insert(p);
	}
	for (point p : Q) {
		if (D.find(p) == D.end()) {
			printf("WA\n");
			return;
		}
	}
	printf("AC\n");
}

int main() {
	int numberOfTestCases = 20;
	for (int i = 1; i <= numberOfTestCases; ++i)
		solveTestCase(i);
}