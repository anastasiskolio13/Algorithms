#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <bit>
#define MAXN 100000
#define MAXP 7
#define INF 1e14
using namespace std;

vector<pair<int, int>> A(MAXN);
vector<vector<int>> S(MAXN, vector<int>(MAXP));
vector<vector<long long>> dp(1 << MAXP, vector<long long>(MAXN + 1));
int N;
int P;
int K;

int C(int s, int i) {
	if (i - (P - popcount(static_cast<unsigned int>(s))) < K)
		return A[i].first;
	return 0;
}

int main() {
	scanf("%d %d %d", &N, &P, &K);
	for (int i = 0; i < N; ++i) {
		scanf("%d", &A[i].first);
		A[i].second = i;
	}
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < P; ++j)
			scanf("%d", &S[i][j]);
	sort(A.begin(), A.begin() + N, greater<pair<int, int>>());
	dp[0][N] = 0;
	for (int s = 1; s < (1 << P); ++s)
		dp[s][N] = -INF;
	for (int i = 0; i < N; ++i)
		dp[0][i] = C(0, i);
	for (int s = 1; s < (1 << P); ++s) {
		for (int i = N - 1; i >= 0; --i) {
			dp[s][i] = dp[s][i + 1] + C(s, i);
			for (int j = 0; j < P; ++j)
				if (s & (1 << j))
					dp[s][i] = max(dp[s][i], dp[s & ~(1 << j)][i + 1] + S[A[i].second][j]);
		}
	}
	printf("%lld\n", dp[(1 << P) - 1][0]);
}