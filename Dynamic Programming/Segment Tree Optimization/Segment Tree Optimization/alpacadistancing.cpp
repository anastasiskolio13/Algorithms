#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 100000
using namespace std;

struct alpaca {
	int A;
	int B;
};

bool compareAlpacas(alpaca X, alpaca Y) {
	return X.A < Y.A;
}

vector<alpaca> A(MAXN);
vector<vector<int>> U(MAXN);
vector<int> R(MAXN);
vector<int> dp(MAXN);
vector<int> T(4 * MAXN);
int N;

int FindActivationPoint(int i) {
	int lo = 0;
	int hi = i - 1;
	while (lo < hi) {
		int j = (lo + hi + 1) / 2;
		if (A[j].A <= A[i].A - A[i].B)
			lo = j;
		else
			hi = j - 1;
	}
	return A[lo].A <= A[i].A - A[i].B ? lo : -1;
}

int FindRight(int i) {
	int lo = i + 1;
	int hi = N - 1;
	while (lo < hi) {
		int j = (lo + hi) / 2;
		if (A[i].A + A[i].B <= A[j].A)
			hi = j;
		else
			lo = j + 1;
	}
	return A[i].A + A[i].B <= A[lo].A ? lo : -1;
}

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
	for (int i = 0; i < N; ++i)
		scanf("%d %d", &A[i].A, &A[i].B);

	sort(A.begin(), A.begin() + N, compareAlpacas);

	for (int i = 1; i < N; ++i) {
		int j = FindActivationPoint(i);
		if (j != -1)
			U[j].push_back(i);
	}

	for (int i = 0; i < N - 1; ++i) 
		R[i] = FindRight(i);

	for (int i = N - 1; i >= 0; --i) {
		for (int j : U[i])
			Update(0, N - 1, 0, j);
		dp[i] = R[i] != -1 ? Query(0, N - 1, 0, R[i], N - 1) + 1 : 1;
	}

	printf("%d\n", *max_element(dp.begin(), dp.begin() + N));
}