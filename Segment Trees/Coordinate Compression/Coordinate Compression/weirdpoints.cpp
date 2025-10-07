#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

struct point {
	int X;
	int Y;
};

bool ComparePoints(point A, point B) {
	return A.X < B.X || A.X == B.X && A.Y < B.Y;
}

int T;
int N;
int K;

void Update(vector<int>& T, vector<int>& I, int lo, int hi, int v, int i) {
	if (lo == hi) {
		T[v] = 1;
		return;
	}
	int mid = (lo + hi) / 2;
	if (I[i] <= mid)
		Update(T, I, lo, mid, 2 * v + 1, i);
	else
		Update(T, I, mid + 1, hi, 2 * v + 2, i);
	T[v] = T[2 * v + 1] + T[2 * v + 2];
}

int Query(vector<int>& T, int lo, int hi, int v, int qlo, int qhi) {
	if (qlo <= lo && hi <= qhi)
		return T[v];
	if (qlo > hi || qhi < lo)
		return 0;
	int mid = (lo + hi) / 2;
	int sumLeft = Query(T, lo, mid, 2 * v + 1, qlo, qhi);
	int sumRight = Query(T, mid + 1, hi, 2 * v + 2, qlo, qhi);
	return sumLeft + sumRight;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &N, &K);
		vector<point> P(N);
		set<pair<int, int>> S;
		vector<int> I(N);
		vector<int> T(4 * N, 0);
		for (int i = 0; i < N; ++i)
			scanf("%d %d", &P[i].X, &P[i].Y);
		sort(P.begin(), P.end(), ComparePoints);
		for (int i = 0; i < N; ++i)
			S.insert({ P[i].Y, i });
		int i = 0;
		for (auto [_, index] : S)
			I[index] = i++;
		int ans = 0;
		for (int i = 0; i < N; ++i) {
			int numberOfDominatedPoints = Query(T, 0, N - 1, 0, 0, I[i]);
			ans += (abs(2 * numberOfDominatedPoints - N + 1) >= K);
			Update(T, I, 0, N - 1, 0, i);
		}
		printf("%d\n", ans);+
	}
}