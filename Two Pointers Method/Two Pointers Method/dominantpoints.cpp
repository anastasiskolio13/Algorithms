#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <cfloat>
#include <set>
#define MAXN 98411
#define INF DBL_MAX
using namespace std;

struct point {
	string ID;
	double X;
	double Y;
};

bool comparePoints(point A, point B) {
	return A.X < B.X;
}

set<string> D;
vector<point> P(MAXN);
vector<double> SMY(MAXN + 1);
int N;

int main() {
	cin >> N;
	for (int i = 0; i < N; ++i)
		cin >> P[i].ID >> P[i].X >> P[i].Y;
	sort(P.begin(), P.begin() + N, comparePoints);
	SMY[N] = -INF;
	for (int i = N - 1; i >= 0; --i)
		SMY[i] = max(SMY[i + 1], P[i].Y);
	int j = 0;
	for (int i = 0; i < N; ++i) {
		while (j < N && P[i].X >= P[j].X)
			++j;
		if (P[i].Y >= SMY[j])
			D.insert(P[i].ID);
	}
	for (string ID : D)
		cout << ID << " ";
	cout << endl;
}