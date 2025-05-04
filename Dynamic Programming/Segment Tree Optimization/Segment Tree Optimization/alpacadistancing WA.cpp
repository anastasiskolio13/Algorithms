#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#define MAXN 100000
using namespace std;

struct Alpaca {
	int A;
	int B;
};

bool compareAlpacas(Alpaca X, Alpaca Y) {
	return X.A < Y.A;
}

set<pair<int, int>> S;
vector<Alpaca> A(MAXN);
vector<int> P(MAXN);
vector<int> T(4 * MAXN);
vector<int> dp(MAXN);
int N;

void Update(int lo, int hi, int v, int i, int x) {
	if (lo == hi) {
		T[v] = x;
		return;
	}
	int mid = (lo + hi) / 2;
	if (i <= mid)
		Update(lo, mid, 2 * v + 1, i, x);
	else
		Update(mid + 1, hi, 2 * v + 2, i, x);
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
	for (int i = 0; i < N; ++i)
		scanf("%d %d", &A[i].A, &A[i].B);
	sort(A.begin(), A.begin() + N, compareAlpacas);
	// Coordinate Compression.
	for (int i = 0; i < N; ++i)
		S.insert({ A[i].A - A[i].B, i });
	int i = 0;
	for (auto Alpaca : S)
		P[Alpaca.second] = i++;
	// Dynamic Programming.
	for (int i = N - 1; i >= 0; --i) {
		auto it = S.lower_bound({ A[i].A + A[i].B, -1 });
		dp[i] = it != S.end() ? Query(0, N - 1, 0, P[it->second], N - 1) + 1 : 1;
		Update(0, N - 1, 0, P[i], dp[i]);
	}
	int maximumDPValue = dp[0];
	for (int i = 1; i < N; ++i)
		maximumDPValue = max(maximumDPValue, dp[i]);
	printf("%d\n", maximumDPValue);
}