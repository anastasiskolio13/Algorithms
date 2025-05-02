#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#include <array>
#define MAXN 70
#define MAXK MAXN - 1
#define INF 1000000000
using namespace std;

set<array<int, 3>> Q;
vector<vector<int>> minimumWeightEdge(MAXN, vector<int>(MAXN));
vector<vector<pair<int, int>>> Adj(MAXN);
vector<vector<vector<int>>> dist(MAXN, vector<vector<int>>(MAXN, vector<int>(MAXK + 1)));
int N;
int M;
int K;
int T;

void Dijkstra(int s) {
	for (int v = 0; v < N; ++v)
		for (int k = 0; k <= K; ++k)
			dist[s][v][k] = INF;
	dist[s][s][0] = 0;
	Q.insert({ 0, s, 0 });
	while (!Q.empty()) {
		int d = (*Q.begin())[0];
		int v = (*Q.begin())[1];
		int j = (*Q.begin())[2];
		Q.erase(Q.begin());
		if (d > dist[s][v][j])
			continue;
		for (auto adjacent : Adj[v]) {
			int u = adjacent.first;
			int w = adjacent.second;
			if (j < K && dist[s][v][j] + w < dist[s][u][j + 1]) {
				dist[s][u][j + 1] = dist[s][v][j] + w;
				Q.insert({ dist[s][u][j + 1], u, j + 1 });
			}
		}
	}
}

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; ++i) {
		int v, u, w;
		scanf("%d %d %d", &v, &u, &w);
		!minimumWeightEdge[--v][--u] ? minimumWeightEdge[v][u] = w : minimumWeightEdge[v][u] = min(minimumWeightEdge[v][u], w);
	}
	// Selecting the minimum weight edge among all the edges connecting v, u.
	for (int v = 0; v < N; ++v)
		for (int u = 0; u < N; ++u)
			if (v != u && minimumWeightEdge[v][u] != 0)
				Adj[v].push_back({ u, minimumWeightEdge[v][u] });
	scanf("%d %d", &K, &T);
	// The shortest path between v, u (if a path exists) it can be more than N - 1 edges.
	K = min(N - 1, K);
	for (int v = 0; v < N; ++v)
		Dijkstra(v);
	while (T--) {
		int v, u;
		scanf("%d %d", &v, &u);
		int ans = dist[--v][--u][0];
		for (int j = 1; j <= K; ++j)
			ans = min(ans, dist[v][u][j]);
		printf("%d\n", ans == INF ? -1 : ans);
	}
}