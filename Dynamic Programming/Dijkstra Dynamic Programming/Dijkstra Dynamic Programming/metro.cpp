#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#include <array>
#define MAXN 10000
#define INF 2e9
using namespace std;

set<array<int, 3>> Q;
vector<vector<pair<int, int>>> Adj(MAXN);
vector<vector<int>> dist(MAXN, vector<int>(2));
int N;
int M;
int T;

void Dijkstra() {
	for (int v = 0; v < N; ++v)
		dist[v][0] = dist[v][1] = INF;
	dist[0][0] = 0;
	Q.insert({ 0, 0, 0 });
	while (!Q.empty()) {
		int d = (*Q.begin())[0];
		int v = (*Q.begin())[1];
		int j = (*Q.begin())[2];
		Q.erase(Q.begin());
		if (d > dist[v][j])
			continue;
		for (auto adjacent : Adj[v]) {
			int u = adjacent.first;
			int w = adjacent.second;
			if ((w || !w && j < 1) && dist[v][j] + w < dist[u][j + !w]) {
				dist[u][j + !w] = dist[v][j] + w;
				Q.insert({ dist[u][j + !w], u, j + !w });
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
	}
	Dijkstra();
	scanf("%d", &T);
	while (T--) {
		int Bi, Di;
		scanf("%d %d", &Bi, &Di);
		--Di;
		printf("%d\n", min(dist[Di][0], dist[Di][1] + Bi));
	}
}