#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <climits>
#include <set>
#include <array>
#define MAXN 100000
#define INF LONG_MAX
using namespace std;

set<array<long, 3>> Q;
vector<vector<pair<int, int>>> Adj(MAXN);
vector<vector<long>> dist(MAXN, vector<long>(2));
int N;
int M;

long Dijkstra() {
	for (int v = 0; v < N; ++v)
		dist[v][0] = dist[v][1] = INF;
	dist[0][0] = 0;
	Q.insert({ 0, 0, 0 });
	while (!Q.empty()) {
		long d = (*Q.begin())[0];
		int v = (int)(*Q.begin())[1];
		int j = (int)(*Q.begin())[2];
		Q.erase(Q.begin());
		if (d > dist[v][j])
			continue;
		for (auto adjacent : Adj[v]) {
			int u = adjacent.first;
			int w = adjacent.second;
			if (dist[v][j] + w < dist[u][j]) {
				dist[u][j] = dist[v][j] + w;
				Q.insert({ dist[u][j], u, j });
			}
			if (j < 1 && dist[v][j] + w / 2 < dist[u][j + 1]) {
				dist[u][j + 1] = dist[v][j] + w / 2;
				Q.insert({ dist[u][j + 1], u, j + 1 });
			}
		}
	}
	return dist[N - 1][1];
}

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; ++i) {
		int v, u, w;
		scanf("%d %d %d", &v, &u, &w);
		Adj[--v].push_back({ --u, w });
	}
	printf("%ld\n", Dijkstra());
}