#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <map>
#include <bit>
#define MAXN 18
#define INF 1e18
using namespace std;

map<pair<int, int>, int> H;
vector<int> A(MAXN);
vector<vector<long long>> dp(1 << MAXN, vector<long long>(MAXN));
int N;
int M;
int K;

int ExtraCost(int i, int j) {
	if (H.find({ i, j }) != H.end())
		return H[{i, j}];
	return 0;
}

int main() {
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 0; i < N; ++i)
		scanf("%d", &A[i]);
	for (int i = 0; i < K; ++i) {
		int Xi, Yi, Ci;
		scanf("%d %d %d", &Xi, &Yi, &Ci);
		H[{--Xi, --Yi}] = Ci;
	}
	for (int s = 0; s < (1 << N); ++s) {
		for (int i = 0; i < N; ++i) {
			if (s & (1 << i)) {
				dp[s][i] = -INF;
				continue;
			}
			int subsetSize = popcount(static_cast<unsigned int>(s));
			if (N - subsetSize == M) {
				dp[s][i] = 0;
				continue;
			}
			if (N - subsetSize > M) {
				dp[s][i] = -INF;
				continue;
			}
			dp[s][i] = -INF;
			for (int j = 0; j < N; ++j)
				if (s & (1 << j))
					dp[s][i] = max(dp[s][i], dp[s & ~(1 << j)][j] + A[j] + ExtraCost(i, j));
		}
	}
	long long maximumSatisfaction = -INF;
	for (int i = 0; i < N; ++i)
		maximumSatisfaction = max(maximumSatisfaction, dp[(1 << N) - 1 & ~(1 << i)][i] + A[i]);
	printf("%lld\n", maximumSatisfaction);
}