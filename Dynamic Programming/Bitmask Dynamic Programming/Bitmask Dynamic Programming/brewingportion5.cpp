#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <bit>
#include <algorithm>
#define MAXN 10
#define INF 1e12
using namespace std;

vector<vector<int>> A(2 * MAXN, vector<int>(2 * MAXN));
vector<pair<int, int>> evenSizeSubsets;
vector<long long> dp(1 << 2 * MAXN);
int N;

int main() {
	scanf("%d", &N);
	for (int i = 0; i < 2 * N; ++i)
		for (int j = 0; j < 2 * N; ++j)
			scanf("%d", &A[i][j]);
	// Κρατάμε μόνο τα υποσύνολα με άρτιο αριθμό στοιχείων.
	for (int s = 0; s < (1 << 2 * N); ++s) {
		int subsetSize = popcount(static_cast<unsigned int>(s));
		if (subsetSize % 2 == 0)
			evenSizeSubsets.push_back({ subsetSize, s });
	}
	// Τα ταξινομούμε με βάση το μέγεθός τους.
	sort(evenSizeSubsets.begin(), evenSizeSubsets.end());
	// Χρησιμοποιούμε ΔΠ.
	dp[0] = 0;
	for (auto [_, s] : evenSizeSubsets)  {
		dp[s] = -INF * (s != 0);
		for (int i = 0; i < 2 * N - 1; ++i) {
			if (!(s & (1 << i)))
				continue;
			for (int j = i + 1; j < 2 * N; ++j)
				if (s & (1 << j))
					dp[s] = max(dp[s], dp[s ^ (1 << i) ^ (1 << j)] + A[i][j]);
		}
	}
	printf("%lld\n", dp[(1 << 2 * N) - 1]);
}