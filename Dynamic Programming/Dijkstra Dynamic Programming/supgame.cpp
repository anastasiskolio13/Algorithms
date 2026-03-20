#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#include <array>
#include <climits>
#define MAXN 60000
#define INF LONG_MAX
using namespace std;

set<array<long long, 3>> Q;
vector<vector<pair<int, int>>> Adj(MAXN);
vector<vector<long long>> dist(MAXN, vector<long long>(2));
int N;
int M;
int s;
int t;
int p;
int q;


void Dijkstra() {
	for (int v = 0; v < N; ++v)
		dist[v][0] = dist[v][1] = INF;
	dist[s][0] = 0;
	Q.insert({ 0, s, 0 });
	while (!Q.empty()) {
		long long d = (*Q.begin())[0];
		int v = (int)(*Q.begin())[1];
		int j = (int)(*Q.begin())[2];
		Q.erase(Q.begin());
		for (auto adjacent : Adj[v]) {
			int u = adjacent.first;
			int w = adjacent.second;
			if (u == q && j == 0)
				continue;
			if (dist[v][j] + w < dist[u][j || !j && u == p]) {
				dist[u][j || !j && u == p] = dist[v][j] + w;
				Q.insert({ dist[u][j || !j && u == p], u, j || !j && u == p });
			}
		}
	}
}

int main() {
	scanf("%d %d %d %d %d %d", &N, &M, &s, &t, &p, &q);
	--s; --t; --p; --q;
	for (int i = 0; i < M; ++i) {
		int v, u, w;
		scanf("%d %d %d", &v, &u, &w);
		Adj[--v].push_back({ --u, w });
	}
	Dijkstra();
	printf("%lld\n", min(dist[t][0], dist[t][1]));
}