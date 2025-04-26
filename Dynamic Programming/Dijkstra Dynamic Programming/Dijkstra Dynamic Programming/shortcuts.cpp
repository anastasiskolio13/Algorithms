#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#include <climits>
#include <array>
#define MAXN 1000
#define INF INT_MAX
using namespace std;

set<array<int, 3>> Q;
vector<vector<pair<int, int>>> Adj(MAXN);
vector<vector<int>> dist(MAXN, vector<int>(MAXN));
int N;
int M;
int s;
int t;
int B;

void Dijkstra(int k) {
	for (int v = 0; v < N; ++v)
		for (int j = 0; j <= k; ++j)
			dist[v][j] = INF;
	dist[s][0] = 0;
	Q.insert({ 0, s, 0 });
	while (!Q.empty()) {
		int d = (*Q.begin())[0];
		int v = (*Q.begin())[1];
		int j = (*Q.begin())[2];
		Q.erase(Q.begin());
		for (auto adjacent : Adj[v]) {
			int u = adjacent.first;
			int w = adjacent.second;
			if (dist[v][j] + w < dist[u][j]) {
				dist[u][j] = dist[v][j] + w;
				Q.insert({ dist[u][j], u, j });
			}
			if (j < k && dist[v][j] < dist[u][j + 1]) {
				dist[u][j + 1] = dist[v][j];
				Q.insert({ dist[u][j + 1], u, j + 1 });
			}
		}
	}
}

int main() {
	scanf("%d %d %d %d %d", &N, &M, &s, &t, &B);
	--s; --t;
	for (int i = 0; i < M; ++i) {
		int v, u, w;
		scanf("%d %d %d", &v, &u, &w);
		Adj[--v].push_back({ --u, w });
	}
	for (int i = 0; i < N; ++i) {
		Dijkstra(i);
		if (dist[t][i] <= B) {
			printf("%d\n", i);
			return 0;
		}
	}
}