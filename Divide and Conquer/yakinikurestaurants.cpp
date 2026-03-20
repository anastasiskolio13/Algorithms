#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 5000
#define MAXM 200
#define INF 1e14
using namespace std;

vector<int> A(MAXN + 1);
vector<vector<int>> B(MAXN + 1, vector<int>(MAXM + 1));
vector<long long> PS(MAXN + 1);
vector<vector<int>> T(4 * MAXN + 1, vector<int>(MAXM + 1));
vector<long long> F(MAXN + 1);
int N;
int M;

void Build(int lo, int hi, int v, int i) {
	if (lo == hi) {
		T[v][i] = B[lo][i];
		return;
	}
	int mid = (lo + hi) / 2;
	Build(lo, mid, 2 * v, i);
	Build(mid + 1, hi, 2 * v + 1, i);
	T[v][i] = max(T[2 * v][i], T[2 * v + 1][i]);
}

int Query(int lo, int hi, int v, int qlo, int qhi, int i) {
	if (qlo <= lo && hi <= qhi)
		return T[v][i];
	if (qlo > hi || qhi < lo)
		return -2e9;
	int mid = (lo + hi) / 2;
	int maxLeft = Query(lo, mid, 2 * v, qlo, qhi, i);
	int maxRight = Query(mid + 1, hi, 2 * v + 1, qlo, qhi, i);
	return max(maxLeft, maxRight);
}

int C(int i, int j, int k) {
	return Query(1, N, 1, i, j, k);
}

void DivideAndConquer(int lo, int hi, int opt_lo, int opt_hi) {
	if (lo > hi)
		return;
	int j = (lo + hi) / 2;
	F[j] = -INF;
	int opt_i;
	for (int i = opt_lo; i <= min(opt_hi, j); ++i) {
		long long fromItoJ = 0;
		for (int k = 1; k <= M; ++k)
			fromItoJ += C(i, j, k);
		if (fromItoJ - PS[j - 1] + PS[i - 1] > F[j]) {
			F[j] = fromItoJ - PS[j - 1] + PS[i - 1];
			opt_i = i;
		}
	}
	DivideAndConquer(lo, j - 1, opt_lo, opt_i);
	DivideAndConquer(j + 1, hi, opt_i, opt_hi);
}

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 1; i < N; ++i) {
		scanf("%d", &A[i]);
		PS[i] = PS[i - 1] + A[i];
	}
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= M; ++j)
			scanf("%d", &B[i][j]);
	for (int j = 1; j <= M; ++j)
		Build(1, N, 1, j);
	DivideAndConquer(1, N, 1, N);
	printf("%lld\n", *max_element(F.begin() + 1, F.begin() + N + 1));
}