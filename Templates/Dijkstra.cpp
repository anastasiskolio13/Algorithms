#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#include <climits>
#define MAXN 1000
#define INF INT_MAX
using namespace std;

set<pair<int, int>> Q;
vector<vector<pair<int, int>>> Adj(MAXN);
vector<int> dist(MAXN);
int N;

void Dijkstra(int s) {
	for (int v = 0; v < N; ++v)
		dist[v] = INF;
	dist[s] = 0;
	Q.insert({ 0, s });
	while (!Q.empty()) {
		auto [d, v] = *Q.begin();
		Q.erase(Q.begin());
		if (d > dist[v])
			continue;
		for (auto [u, w] : Adj[v]) {
			if (dist[v] + w < dist[u]) {
				dist[u] = dist[v] + w;
				Q.insert({ dist[u], u });
			}
		}
	}
}