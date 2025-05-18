#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#define MAXN 100000
#define INF 1e18
using namespace std;

set<pair<long long, int>> Q;
vector<vector<pair<int, int>>> Adj(MAXN + 1);
vector<long long> dist(MAXN + 1);
int N;
int M;
int K;
int T;

void MultiSourceDijkstra() {
	for (int v = 0; v < N; ++v)
		dist[v] = INF;
	dist[N] = 0;
	Q.insert({ 0, N });
	while (!Q.empty()) {
		long long d = Q.begin()->first;
		int v = Q.begin()->second;
		Q.erase(Q.begin());
		if (d > dist[v])
			continue;
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
	scanf("%d %d %d %d", &N, &M, &K, &T);
	for (int i = 0; i < M; ++i) {
		int v, u, w;
		scanf("%d %d %d", &v, &u, &w);
		Adj[--v].push_back({ --u, w });
		Adj[u].push_back({ v, w });
	}
	for (int i = 0; i < K; ++i) {
		int s;
		scanf("%d", &s);
		Adj[N].push_back({ --s, 0 });
	}
	MultiSourceDijkstra();
	while (T--) {
		int v;
		scanf("%d", &v);
		printf("%lld\n", dist[--v]);
	}
}