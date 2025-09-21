#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#define MAXN 100000
#define MAXQ 100000
using namespace std;

vector<int> A(MAXN);
vector<int> B(MAXN);
vector<long long> T(4 * MAXN);
vector<long long> L(4 * MAXN);
vector<pair<int, int>> R(MAXN);
vector<array<int, 3>> U(MAXQ);
vector<vector<int>> TS(MAXN);
int N;
int Q;

void lazyUpdate(int lo, int hi, int v, int qlo, int qhi, int x) {
	if (L[v] != 0) {
		T[v] += L[v];
		if (lo != hi) {
			L[2 * v + 1] += L[v];
			L[2 * v + 2] += L[v];
		}
		L[v] = 0;
	}
	if (qlo <= lo && hi <= qhi) {
		T[v] += x;
		if (lo != hi) {
			L[2 * v + 1] += x;
			L[2 * v + 2] += x;
		}
		return;
	}
	if (qlo > hi || qhi < lo)
		return;
	int mid = (lo + hi) / 2;
	lazyUpdate(lo, mid, 2 * v + 1, qlo, qhi, x);
	lazyUpdate(mid + 1, hi, 2 * v + 2, qlo, qhi, x);
}

long long lazyQuery(int lo, int hi, int v, int qlo, int qhi) {
	if (L[v] != 0) {
		T[v] += L[v];
		if (lo != hi) {
			L[2 * v + 1] += L[v];
			L[2 * v + 2] += L[v];
		}
		L[v] = 0;
	}
	if (qlo <= lo && hi <= qhi)
		return T[v];
	if (qlo > hi || qhi < lo)
		return 0;
	int mid = (lo + hi) / 2;
	long long sumLeft = lazyQuery(lo, mid, 2 * v + 1, qlo, qhi);
	long long sumRight = lazyQuery(mid + 1, hi, 2 * v + 2, qlo, qhi);
	return sumLeft + sumRight;
}

int main() {
	scanf("%d %d", &N, &Q);
	for (int i = 0; i < N; ++i) {
		scanf("%d", &A[i]);
		R[i] = { 0, Q - 1 };
	}
	for (int i = 0; i < Q; ++i) {
		scanf("%d %d %d", &U[i][0], &U[i][1], &U[i][2]);
		--U[i][0];
		--U[i][1];
	}
	for (int i = 0; i < ceil(log2(Q)); i++) {
		for (int j = 0; j < Q; ++j)
			TS[j].clear();
		for (int j = 0; j < N; ++j) {
			auto [lo, hi] = R[j];
			if (lo < hi)
				TS[(lo + hi) / 2].push_back(j);
		}
		lazyUpdate(0, N - 1, 0, 0, N - 1, 0);
		for (int j = 0; j < Q; ++j) {
			lazyUpdate(0, N - 1, 0, U[j][0], U[j][1], U[j][2]);
			for (int k : TS[j]) {
				if (lazyQuery(0, N - 1, 0, k, k) >= A[k])
					R[k].second = j;
				else
					R[k].first = j + 1;
			}
		}
	}
	for (int i = 0; i < Q; ++i)
		TS[i].clear();
	for (int i = 0; i < N; ++i)
		TS[R[i].first].push_back(i);
	lazyUpdate(0, N - 1, 0, 0, N - 1, 0);
	for (int i = 0; i < Q; ++i) {
		lazyUpdate(0, N - 1, 0, U[i][0], U[i][1], U[i][2]);
		for (int j : TS[i]) {
			if (lazyQuery(0, N - 1, 0, j, j) >= A[j])
				B[j] = i + 1;
			else
				B[j] = -1;
		}
	}
	for (int i = 0; i < N; ++i)
		printf("%d ", B[i]);
}