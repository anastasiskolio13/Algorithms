#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#define MAXN 100000
#define INF 1000000000
using namespace std;

set<pair<int, int>> S;
vector<int> H(MAXN + 1);
vector<int> P(MAXN + 1);
vector<pair<int, int>> T(4 * MAXN + 1);
vector<int> dp(MAXN + 1);
int N;
int K;

void Update(int lo, int hi, int v, int i, int x, int y) {
	if (lo == hi) {
		T[v].first = x;
		T[v].second = y;
		return;
	}
	int mid = (lo + hi) / 2;
	if (i <= mid)
		Update(lo, mid, 2 * v, i, x, y);
	else
		Update(mid + 1, hi, 2 * v + 1, i, x, y);
	T[v].first = min(T[2 * v].first, T[2 * v + 1].first);
	T[v].second = min(T[2 * v].second, T[2 * v + 1].second);
}

int Query(int lo, int hi, int v, int qlo, int qhi, int x) {
	if (qlo > qhi)
		return INF;
	if (qlo <= lo && hi <= qhi)
		return x ? T[v].second : T[v].first;
	if (qlo > hi || qhi < lo)
		return INF;
	int mid = (lo + hi) / 2;
	int minLeft = Query(lo, mid, 2 * v, qlo, qhi, x);
	int minRight = Query(mid + 1, hi, 2 * v + 1, qlo, qhi, x);
	return min(minLeft, minRight);
}

int main() {
	scanf("%d %d", &N, &K);
	for (int i = 1; i <= N; ++i) {
		scanf("%d", &H[i]);
		S.insert({ H[i], i });
	}
	int i = 1;
	for (auto stone : S) {
		dp[i] = INF;
		Update(1, N, 1, P[stone.second], INF, INF);
		P[stone.second] = i++;
	}
	dp[N] = 0;
	Update(1, N, 1, P[N], dp[N] - H[N], dp[N] + H[N]);
	for (int i = N - 1; i >= 1; --i) {
		if (i + K < N)
			Update(1, N, 1, P[i + K + 1], INF, INF);
		auto it = S.upper_bound({H[i], N});
		int minLeft = Query(1, N, 1, 1, P[i] - 1, 0) + H[i];
		int minRight = it != S.end() ? Query(1, N, 1, it->second, N, 1) - H[i] : INF;
		dp[i] = min(minLeft, minRight);
		Update(1, N, 1, P[i], dp[i] - H[i], dp[i] + H[i]);
	}
	printf("%d\n", dp[1]);
}