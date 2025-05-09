#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 100000
using namespace std;

vector<int> L(MAXN);
vector<int> R(MAXN);
vector<int> C(MAXN);
vector<vector<int>> U(MAXN);
vector<int> dp(MAXN);
vector<int> T(4 * MAXN);
int N;

void Update(int lo, int hi, int v, int i) {
	if (lo == hi) {
		T[v] = dp[i];
		return;
	}
	int mid = (lo + hi) / 2;
	if (i <= mid)
		Update(lo, mid, 2 * v + 1, i);
	else
		Update(mid + 1, hi, 2 * v + 2, i);
	T[v] = max(T[2 * v + 1], T[2 * v + 2]);
}

int Query(int lo, int hi, int v, int qlo, int qhi) {
	if (qlo <= lo && hi <= qhi)
		return T[v];
	if (qlo > hi || qhi < lo)
		return 0;
	int mid = (lo + hi) / 2;
	int maxLeft = Query(lo, mid, 2 * v + 1, qlo, qhi);
	int maxRight = Query(mid + 1, hi, 2 * v + 2, qlo, qhi);
	return max(maxLeft, maxRight);
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		scanf("%d %d %d", &C[i], &L[i], &R[i]);
		if (i - L[i] - 1 >= 0)
			U[i - L[i] - 1].push_back(i);
	}
	for (int i = N - 1; i >= 0; --i) {
		for (int j : U[i])
			Update(0, N - 1, 0, j);
		dp[i] = i + R[i] + 1 <= N - 1 ? Query(0, N - 1, 0, i + R[i] + 1, N - 1) + C[i] : C[i];
		if (!L[i])
			Update(0, N - 1, 0, i);
	}
	printf("%d\n", *max_element(dp.begin(), dp.begin() + N));
}