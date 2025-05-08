#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#include <climits>
#define MAXN 200000
#define INF LLONG_MAX
using namespace std;

set<pair<int, int>> S;
vector<int> A(MAXN);
vector<int> P(MAXN);
vector<vector<long long>> dp(MAXN, vector <long long>(2));
vector<long long> T(4 * MAXN);
vector<long long> prefix(MAXN);
vector<long long> suffix(MAXN);
int N;
long long C;

void Update(int lo, int hi, int v, int i, long long x) {
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

long long Query(int lo, int hi, int v, int qlo, int qhi) {
	if (qlo <= lo && hi <= qhi)
		return T[v];
	if (qlo > hi || qhi < lo)
		return 0;
	int mid = (lo + hi) / 2;
	long long maxLeft = Query(lo, mid, 2 * v + 1, qlo, qhi);
	long long maxRight = Query(mid + 1, hi, 2 * v + 2, qlo, qhi);
	return max(maxLeft, maxRight);
}

int main() {
	scanf("%d %lld", &N, &C);
	for (int i = 0; i < N; ++i) {
		scanf("%d", &A[i]);
		S.insert({ A[i], i });
	}
	// Coordinate Compression.
	int i = 0;
	for (auto a : S)
		P[a.second] = i++;
	for (int i = N - 1; i >= 0; --i) {
		auto it = S.upper_bound({ A[i], N });
		suffix[i] = it != S.end() ? Query(0, N - 1, 0, P[it->second], N - 1) + A[i] : A[i];
		Update(0, N - 1, 0, P[i], suffix[i]);
	}
	T.assign(4 * MAXN, 0);
	for (int i = 0; i < N; ++i) {
		auto it = S.upper_bound({ A[i], N });
		prefix[i] = it != S.end() ? Query(0, N - 1, 0, P[it->second], N - 1) + A[i] : A[i];
		Update(0, N - 1, 0, P[i], prefix[i]);
	}
	long long optimalDP = 0;
	for (int i = 0; i < N; ++i) {
		dp[i][0] = max(suffix[i], prefix[i] - C);
		dp[i][1] = max(suffix[i] - C, prefix[i]);
		optimalDP = max({ optimalDP, dp[i][0], dp[i][1], (long long) A[i]});
	}
	printf("%lld\n", optimalDP);
}