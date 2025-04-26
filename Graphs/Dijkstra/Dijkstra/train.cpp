#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <array>
#include <climits>
#include <set>
#include <cmath>
#define MAXN 100000
#define INF LLONG_MAX
using namespace std;

set<pair<long long, int>> Q;
vector<vector<array<int, 3>>> Adj(MAXN);
vector<long long> dist(MAXN);
int N;
int M;
int X;
int Y;

void Dijkstra() {
	for (int v = 0; v < N; ++v)
		dist[v] = INF;
	dist[X] = 0;
	Q.insert({ 0, X });
	while (!Q.empty()) {
		long long d = Q.begin()->first;
		int v = Q.begin()->second;
		Q.erase(Q.begin());
		if (d > dist[v])
			continue;
		for (auto adjacent : Adj[v]) {
			int u = adjacent[0];
			int t = adjacent[1];
			int k = adjacent[2];
			int waitingTime = k * ceil((double)dist[v] / k) - dist[v];
			if (dist[v] + waitingTime + t < dist[u]) {
				dist[u] = dist[v] + waitingTime + t;
				Q.insert({ dist[u], u });
			}
		}
	}
}

int main() {
	scanf("%d %d %d %d", &N, &M, &X, &Y);
	--X; --Y;
	for (int i = 0; i < M; ++i) {
		int a, b, t, k;
		scanf("%d %d %d %d", &a, &b, &t, &k);
		Adj[--a].push_back({ --b, t, k });
		Adj[b].push_back({ a, t, k });
	}
	Dijkstra();
	printf("%lld\n", dist[Y] != INF ? dist[Y] : -1);
}