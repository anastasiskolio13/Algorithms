#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#define MAXN 50	
#define INF 2e9
#define MAXT 300
using namespace std;

set<pair<int, int>> Q;
vector<vector<pair<int, int>>> Adj(MAXN);
vector<int> D(MAXN, INF);
vector<int> S(MAXN);
int dp[2][MAXT + 2][MAXT + 2][MAXT + 2];
int N;
int M;

void Dijkstra() {
	D[0] = 0;
	Q.insert({ 0, 0 });
	while (!Q.empty()) {
		auto [d, v] = *Q.begin();
		Q.erase(Q.begin());
		if (d > D[v])
			continue;
		for (auto [u, w] : Adj[v]) {
			if (D[v] + w < D[u]) {
				D[u] = D[v] + w;
				Q.insert({ D[u], u });
			}
		}
	}
}

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; ++i) {
		int v, u, w;
		scanf("%d %d %d", &v, &u, &w);
		Adj[v].push_back({ u, w });
		Adj[u].push_back({ v, w });
	}
	Dijkstra();
	for (int i = 1; i < N; ++i)
		S[i] = S[i - 1] + D[i];
	for (int T1 = 0; T1 <= min(S[N - 1], MAXT + 1); ++T1) {
		for (int T2 = 0; T2 <= min(S[N - 1] - T1, MAXT + 1); ++T2) {
			for (int T3 = 0; T3 <= min(S[N - 1] - T1 - T2, MAXT + 1); ++T3) {
				int T4 = S[N - 1] - (T1 + T2 + T3);
				int maximumTime = max({ T1, T2, T3, T4 });
				dp[N % 2][T1][T2][T3] = maximumTime <= MAXT ? maximumTime : INF;
			}
		}
	}
	for (int i = N - 1; i >= 1; --i)
		for (int T1 = 0; T1 <= min(S[i], MAXT + 1); ++T1)
			for (int T2 = 0; T2 <= min(S[i] - T1, MAXT + 1); ++T2)
				for (int T3 = 0; T3 <= min(S[i] - T1 - T2, MAXT + 1); ++T3)
					dp[i % 2][T1][T2][T3] = min({ dp[(i + 1) % 2][min(T1 + D[i], MAXT + 1)][T2][T3],
												 dp[(i + 1) % 2][T1][min(T2 + D[i], MAXT + 1)][T3],
												 dp[(i + 1) % 2][T1][T2][min(T3 + D[i], MAXT + 1)],
												 dp[(i + 1) % 2][T1][T2][T3] });
	dp[1][0][0][0] != INF ? printf("%d\n", 2 * dp[1][0][0][0]) : printf("Impossible!\n");
}