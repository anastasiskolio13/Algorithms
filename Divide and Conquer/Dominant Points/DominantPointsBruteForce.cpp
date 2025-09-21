#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
using namespace std;

struct point {
	int X;
	int Y;
};

void solveTestCase(int j) {
	string filenameOne = "in" + to_string(j) + ".txt";
	freopen(filenameOne.c_str(), "r", stdin);
	int N;
	scanf("%d", &N);
	vector<point> P(N);
	for (int i = 0; i < N; ++i)
		scanf("%d %d", &P[i].X, &P[i].Y);
	set<pair<int, int>> D;
	for (int i = 0; i < N; ++i) {
		bool isDominant = true;
		for (int j = 0; j < N; ++j) { 
			if (i == j)
				continue;
			if (P[j].X >= P[i].X && P[j].Y >= P[i].Y)
				isDominant = false;
		}
		if (isDominant)
			D.insert({ P[i].X, P[i].Y });
	}
	string filenameTwo = "out" + to_string(j) + ".txt";
	freopen(filenameTwo.c_str(), "w", stdout);
	printf("%d\n", D.size());
	for (auto [X, Y] : D)
		printf("%d %d\n", X, Y);
}

int main() {
	int numberOfTestCases = 20;
	for (int i = 1; i <= numberOfTestCases; ++i)
		solveTestCase(i);
}
