#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#define MAXN 10000
#define INF 1000000
using namespace std;

queue<int> Q;
vector<vector<int>> Adj(MAXN);
vector<int> dist(MAXN);
int N;

int BreadthFirstSearch() {
	for (int v = 0; v < N; ++v)
		dist[v] = INF;
	int totalVisited = 0;
	dist[0] = 1;
	Q.push(0);
	while (!Q.empty()) {
		++totalVisited;
		int v = Q.front();
		Q.pop();
		for (int u : Adj[v]) {
			if (dist[u] == INF) {
				dist[u] = dist[v] + 1;
				Q.push(u);
			}
		}
	}
	return totalVisited;
}

int main() {
	scanf("%d", &N);
	for (int v = 0; v < N; ++v) {
		int M;
		scanf("%d", &M);
		for (int j = 0; j < M; ++j) {
			int u;
			scanf("%d", &u);
			Adj[v].push_back(--u);
		}
	}
	int totalVisited = BreadthFirstSearch();
	int minimumCostPath = N;
	for (int v = 0; v < N; ++v)
		if (Adj[v].empty() && dist[v] < minimumCostPath)
			minimumCostPath = dist[v];
	totalVisited == N ? printf("Y\n%d\n", minimumCostPath) : printf("N\n%d\n", minimumCostPath);
}