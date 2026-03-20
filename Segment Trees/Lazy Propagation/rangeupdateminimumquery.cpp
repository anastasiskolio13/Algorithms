#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 100000
#define INF 1e18
using namespace std;

vector<int> A(MAXN);
vector<long long> T(4 * MAXN);
vector<long long> L(4 * MAXN);
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
	T[v] = min(T[2 * v + 1], T[2 * v + 2]);
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
		return INF;
	int mid = (lo + hi) / 2;
	long long minLeft = lazyQuery(lo, mid, 2 * v + 1, qlo, qhi);
	long long minRight = lazyQuery(mid + 1, hi, 2 * v + 2, qlo, qhi);
	return min(minLeft, minRight);
}

int main() {
	scanf("%d %d", &N, &Q);
	for (int i = 0; i < N; ++i) {
		scanf("%d", &A[i]);
		lazyUpdate(0, N - 1, 0, i, i, A[i]);
	}
	while (Q--) {
		int a, b, c, d;
		scanf("%d %d %d", &a, &b, &c);
		if (a == 1) {
			scanf("%d", &d);
			lazyUpdate(0, N - 1, 0, b - 1, c - 1, d);
		}
		else {
			printf("%lld\n", lazyQuery(0, N - 1, 0, b - 1, c - 1));
		}
	}
}