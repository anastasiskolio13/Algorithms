#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#define MAXN 1000
#define INF INT_MAX
using namespace std;

set<pair<int, int>> Q;
vector<vector<pair<int, int>>> Adj(MAXN);
vector<int> dist(MAXN);
vector<bool> S(MAXN);
int N;

void Dijkstra(int s) {
	for (int v = 0; v < N; ++v)
		dist[v] = INF;
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