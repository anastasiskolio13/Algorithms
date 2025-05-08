#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
#define MAXN 1000
#define MAXT_max 1000
#define INF INT_MAX
using namespace std;

vector<int> P(MAXN);
vector<vector<int>> Adj(MAXN);
vector<vector<int>> dp(2, vector<int>(MAXN));
int N;
int M;
int C;

int main() {
	freopen("time.in", "r", stdin);
	freopen("time.out", "w", stdout);
	scanf("%d %d %d", &N, &M, &C);
	for (int v = 0; v < N; ++v)
		scanf("%d", &P[v]);
	for (int i = 0; i < M; ++i) {
		int v, u;
		scanf("%d %d", &v, &u);
		Adj[--v].push_back(--u);
	}
	// Maximum number of days that a trip can last to be profitable.
	int T_max = ceil((double)*max_element(P.begin(), P.begin() + N) / C) - 1;
	dp[T_max % 2][0] = -C * T_max * T_max;
	for (int v = 1; v < N; ++v)
		dp[T_max % 2][v] = -INF;
	for (int T = T_max - 1; T >= 0; --T) {
		dp[T % 2][0] = -C * T * T;
		for (int u : Adj[0])
			dp[T % 2][0] = max(dp[T % 2][0], dp[(T + 1) % 2][u]);
		for (int v = 1; v < N; ++v) {
			dp[T % 2][v] = -INF;
			for (int u : Adj[v])
				dp[T % 2][v] = max(dp[T % 2][v], dp[(T + 1) % 2][u] + P[v]);
		}
	}
	printf("%d\n", dp[0][0]);
}