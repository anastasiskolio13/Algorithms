#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 2500
#define INF 1e18
using namespace std;

vector<vector<pair<int, int>>> Adj(MAXN);
vector<vector<long long>> dp(MAXN, vector<long long>(MAXN));
int N;
int M;

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; ++i) {
		int v, u, w;
		scanf("%d %d %d", &v, &u, &w);
		Adj[--v].push_back({ --u, w });
	}
	for (int i = 0; i < N; ++i)
		dp[N - 1][i] = 0;
	for (int v = 0; v < N - 1; ++v)
		dp[v][0] = -INF;
	for (int i = 1; i < N; ++i) {
		for (int v = 0; v < N - 1; ++v) {
			dp[v][i] = -INF;
			for (auto [u, w] : Adj[v])
				dp[v][i] = max(dp[v][i], dp[u][i - 1] + w);
		}
	}
	printf("%lld\n", dp[0][N - 1]);
}