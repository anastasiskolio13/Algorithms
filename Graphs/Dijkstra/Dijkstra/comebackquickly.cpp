#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <climits>
#include <set>
#define MAXN 2000
#define INF 1000000000
using namespace std;

set<pair<int, int>> Q;
vector<vector<pair<int, int>>> Adj(MAXN);
vector<int> minimumWalkDistance(MAXN);
vector<vector<int>> dist(MAXN, vector<int>(MAXN));
int N;
int M;

void Dijkstra(int s) {
	for (int v = 0; v < N; ++v)
		dist[s][v] = INF;
	dist[s][s] = 0;
	Q.insert({ 0, s });
	while (!Q.empty()) {
		int d = Q.begin()->first;
		int v = Q.begin()->second;
		Q.erase(Q.begin());
		if (d > dist[s][v])
			continue;
		for (auto adjacent : Adj[v]) {
			int u = adjacent.first;
			int w = adjacent.second;
			if (dist[s][v] + w < dist[s][u]) {
				dist[s][u] = dist[s][v] + w;
				Q.insert({ dist[s][u], u });
			}
		}
	}
}

int main() {
	scanf("%d %d", &N, &M);
	for (int v = 0; v < N; ++v)
		minimumWalkDistance[v] = INF;
	for (int i = 0; i < M; ++i) {
		int v, u, w;
		scanf("%d %d %d", &v, &u, &w);
		Adj[--v].push_back({ --u, w });
		if (v == u)
			minimumWalkDistance[v] = min(minimumWalkDistance[v], w);
	}
	for (int v = 0; v < N; ++v)
		Dijkstra(v);
	for (int v = 0; v < N; ++v) {
		for (int u = 0; u < N; u++)
			if (v != u && dist[v][u] + dist[u][v] < minimumWalkDistance[v])
				minimumWalkDistance[v] = dist[v][u] + dist[u][v];
		printf("%d\n", minimumWalkDistance[v] == INF ? -1 : minimumWalkDistance[v]);
	}
}