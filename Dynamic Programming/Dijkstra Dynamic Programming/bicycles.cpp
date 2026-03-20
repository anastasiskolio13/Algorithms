#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <tuple>
#define MAXN 1000
#define MAXS 1000
#define INF 1e18
using namespace std;

set<tuple<long long, int, int>> Q;
vector<vector<pair<int, int>>> Adj;
vector<int> S(MAXN);
vector<vector<long long>> dp(MAXN, vector<long long>(MAXS + 1));
int T;
int N;
int M;

long long Dijkstra() {
	for (int v = 0; v < N; ++v)
		for (int s = *min_element(S.begin(), S.begin() + N); s <= *max_element(S.begin(), S.begin() + N); ++s)
			dp[v][s] = INF;
	dp[0][S[0]] = 0;
	Q.insert({ 0, 0, S[0] });
	while (!Q.empty()) {
		auto [d, v, s] = *Q.begin();
		Q.erase(Q.begin());
		if (d > dp[v][s])
			continue;
		for (auto [u, w] : Adj[v]) {
			if (dp[v][s] + (long long)w * s < dp[u][min(s, S[u])]) {
				dp[u][min(s, S[u])] = dp[v][s] + (long long)w * s;
				Q.insert({ dp[u][min(s, S[u])], u, min(s, S[u]) });
			}
		}
	}
	long long minimumDistance = INF;
	for (int s = *min_element(S.begin(), S.begin() + N); s <= *max_element(S.begin(), S.begin() + N); ++s)
		minimumDistance = min(minimumDistance, dp[N - 1][s]);
	return minimumDistance;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &N, &M);
		Adj.clear();
		Adj.resize(N);
		for (int i = 0; i < M; ++i) {
			int v, u, w;
			scanf("%d %d %d", &v, &u, &w);
			Adj[--v].push_back({ --u, w });
			Adj[u].push_back({ v, w });
		}
		for (int i = 0; i < N; ++i)
			scanf("%d", &S[i]);
		printf("%lld\n", Dijkstra());
	}
}