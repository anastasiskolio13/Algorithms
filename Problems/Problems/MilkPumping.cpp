#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <climits>
#include <array>
#include <set>
#define MAXN 1000
#define INF INT_MAX
using namespace std;

set<pair<int, int>> Q;
vector<vector<array<int, 3>>> Adj(MAXN);
vector<int> dist(MAXN);
int N;
int M;

int Dijkstra(int flowRate) {
	for (int v = 0; v < N; ++v)
		dist[v] = INF;
	dist[0] = 0;
	Q.insert({ 0, 0 });
	while (!Q.empty()) {
		int d = Q.begin()->first;
		int v = Q.begin()->second;
		Q.erase(Q.begin());
		for (auto adjacent : Adj[v]) {
			int u = adjacent[0];
			int c = adjacent[1];
			int f = adjacent[2];
			if (f >= flowRate && dist[v] + c < dist[u]) {
				dist[u] = dist[v] + c;
				Q.insert({ dist[u], u });
			}
		}
	}
	return (double)flowRate / dist[N - 1] * 1000000;
}

int main() {
	freopen("pump.in", "r", stdin);
	freopen("pump.out", "w", stdout);
	scanf("%d %d", &N, &M);
	int minimumFlowRate = 1000;
	int maximumFlowRate = 0;
	for (int i = 0; i < M; ++i) {
		int v, u, c, f;
		scanf("%d %d %d %d", &v, &u, &c, &f);
		Adj[--v].push_back({ --u, c, f });
		Adj[u].push_back({ v, c, f });
		minimumFlowRate = min(minimumFlowRate, f);
		maximumFlowRate = max(maximumFlowRate, f);
	}
	// Linear Search the Answer.
	int ans = 0;
	for (int flowRate = minimumFlowRate; flowRate <= maximumFlowRate; ++flowRate)
		ans = max(ans, Dijkstra(flowRate));
	printf("%d\n", ans);
}