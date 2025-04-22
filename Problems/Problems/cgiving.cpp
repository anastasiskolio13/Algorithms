#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#define MAXN 50000
#define INF INT_MAX
using namespace std;

set<pair<int, int>> Q;
vector<vector<pair<int, int>>> Adj(MAXN);
vector<int> dist(MAXN);
int N;
int B;
int M;

void Dijkstra(int s) {
	for (int v = 0; v < N; ++v)
		dist[v] = INF;
	dist[0] = 0;
	Q.insert({ 0, s });
	while (!Q.empty()) {
		int d = Q.begin()->first;
		int v = Q.begin()->second;
		Q.erase(Q.begin());
		for (auto adjacent : Adj[v]) {
			int u = adjacent.first;
			int w = adjacent.second;
			if (dist[v] + w < dist[u]) {
				dist[u] = dist[v] + w;
				Q.insert({ dist[u], u });
			}
		}
	}
}

int main() {
	scanf("%d %d %d", &N, &M, &B);
	for (int i = 0; i < M; ++i) {
		int v, u, w;
		scanf("%d %d %d", &v, &u, &w);
		Adj[--v].push_back({ --u, w });
		Adj[u].push_back({ v, w });
	}
	Dijkstra(0);
	while (B--) {
		int v, u;
		scanf("%d %d", &v, &u);
		printf("%d\n", dist[--v] + dist[--u]);
	}
}