#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 200000
using namespace std;

vector<pair<int, int>> A(MAXN);
vector<vector<long long>> dp(MAXN, vector<long long>(2));
vector<pair<long long, long long>> T(4 * MAXN);
int N;
long long C;

void Update(int lo, int hi, int v, int i) {
	if (lo == hi) {
		T[v].first = dp[i][0];
		T[v].second = dp[i][1];
		return;
	}
	int mid = (lo + hi) / 2;
	if (i <= mid)
		Update(lo, mid, 2 * v + 1, i);
	else
		Update(mid + 1, hi, 2 * v + 2, i);
	T[v].first = max(T[2 * v + 1].first, T[2 * v + 2].first);
	T[v].second = max(T[2 * v + 1].second, T[2 * v + 2].second);
}

long long Query(int lo, int hi, int v, int qlo, int qhi, int id) {
	if (qlo <= lo && hi <= qhi)
		return T[v].first * !id + T[v].second * id;
	if (qlo > hi || qhi < lo)
		return 0;
	int mid = (lo + hi) / 2;
	long long maxLeft = Query(lo, mid, 2 * v + 1, qlo, qhi, id);
	long long maxRight = Query(mid + 1, hi, 2 * v + 2, qlo, qhi, id);
	return max(maxLeft, maxRight);
}

int main() {
	scanf("%d %lld", &N, &C);
	for (int i = 0; i < N; ++i) {
		scanf("%d", &A[i].first);
		A[i].second = i;
	}
	sort(A.begin(), A.begin() + N, greater<pair<int, int>>());
	for (int i = 0; i < N; ++i) {
		long long GoRight = Query(0, N - 1, 0, A[i].second + 1, N - 1, 0);
		long long GoLeft = Query(0, N - 1, 0, 0, A[i].second - 1, 1);
		dp[A[i].second][0] = max(max(GoRight, GoLeft - C) + A[i].first, (long long) A[i].first);
		dp[A[i].second][1] = max(max(GoRight - C, GoLeft) + A[i].first, (long long) A[i].first);
		Update(0, N - 1, 0, A[i].second);
	}
	long long optimalDP = 0;
	for (int i = 0; i < N; ++i)
		optimalDP = max({ optimalDP, dp[i][0], dp[i][1] });
	printf("%lld\n", optimalDP);
}

