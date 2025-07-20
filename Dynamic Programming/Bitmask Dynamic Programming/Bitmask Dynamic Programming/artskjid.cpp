#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 18
#define INF 1e18
using namespace std;

vector<vector<pair<int, int>>> Adj(MAXN);
vector<vector<long long>> dp(1 << MAXN, vector<long long>(MAXN));
int N;
int M;

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; ++i) {
		int v, u, w;
		scanf("%d %d %d", &v, &u, &w);
		Adj[v].push_back({ u, w });
	}
	for (int s = 0; s < (1 << N); ++s)
		dp[s][N - 1] = 0;
	for (int s = 0; s < (1 << N); ++s) {
		for (int i = 0; i < N - 1; ++i) {
			dp[s][i] = -INF;
			for (auto [j, w] : Adj[i])
				if (s & (1 << j))
					dp[s][i] = max(dp[s][i], dp[s & ~(1 << j)][j] + w);
		}
	}
	printf("%lld\n", dp[(1 << N) - 1 & ~(1 << 0)][0]);
}