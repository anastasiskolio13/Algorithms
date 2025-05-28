#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#include <climits>
#include <algorithm>
#define MAXN 100000
#define INF LLONG_MAX
using namespace std;

set<pair<int, long long>> Q;
vector<vector<pair<int, int>>> Adj(MAXN);
vector<long long> dist(MAXN);
vector<int> P(MAXN);
vector<int> path;
int N;
int M;

void Dijkstra() {
	for (int v = 0; v < N; ++v)
		dist[v] = INF;
	dist[0] = 0;
	Q.insert({ 0, 0 });
	while (!Q.empty()) {
		auto [d, v] = *Q.begin();
		Q.erase(Q.begin());
		if (d > dist[v])
			continue;
		for (auto node : Adj[v]) {
			auto [u, w] = node;
			if (dist[v] + w < dist[u]) {
				dist[u] = dist[v] + w;
				P[u] = v;
				Q.insert({ dist[u], u });
			}
		}
	}
}

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; ++i) {
		int v, u, w;
		scanf("%d %d %d", &v, &u, &w);
		Adj[--v].push_back({ --u, w });
		Adj[u].push_back({ v, w });
	}
	Dijkstra();
	if (dist[N - 1] == INF) {
		printf("-1");
		return 0;
	}
	int v = N - 1;
	while (v != 0) {
		path.push_back(v + 1);
		v = P[v];
	}
	path.push_back(1);
	reverse(path.begin(), path.end());
	for (int v : path)
		printf("%d ", v);
}