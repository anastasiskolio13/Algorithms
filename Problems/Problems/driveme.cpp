#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#include <array>
#include <climits>
#define MAXN 100
#define MAXK 10
#define INF INT_MAX
using namespace std;

set<array<int, 3>> Q;
vector<vector<pair<int, int>>> AdjOne(MAXN);
vector<vector<pair<int, int>>> AdjTwo(MAXN);
vector<vector<vector<int>>> dist(MAXN, vector<vector<int>>(MAXN, vector<int>(MAXK + 1)));
int N;
int M;
int K;
int T;

void Dijkstra(int s) {
	for (int v = 0; v < N; v++)
		for (int k = 0; k <= K; ++k)
			dist[s][v][k] = INF;
	dist[s][s][0] = 0;
	Q.insert({ 0, s, 0 });
	while (!Q.empty()) {
		int d = (*Q.begin())[0];
		int v = (*Q.begin())[1];
		int j = (*Q.begin())[2];
		Q.erase(Q.begin());
		for (auto adjacent : AdjOne[v]) {
			int u = adjacent.first;
			int w = adjacent.second;
			if (dist[s][v][j] + w < dist[s][u][j]) {
				dist[s][u][j] = dist[s][v][j] + w;
				Q.insert({ dist[s][u][j], u, j });
			}
		}
		for (auto adjacent : AdjTwo[v]) {
			int u = adjacent.first;
			int w = adjacent.second;
			if (j < K && dist[s][v][j] + w < dist[s][u][j + 1]) {
				dist[s][u][j + 1] = dist[s][v][j] + w;
				Q.insert({ dist[s][u][j + 1], u, j + 1 });
			}
		}
	}
}

int main() {
	scanf("%d %d %d %d", &N, &M, &K, &T);
	for (int i = 0; i < M; ++i) {
		int v, u, w;
		scanf("%d %d %d", &v, &u, &w);
		AdjOne[--v].push_back({ --u, w });
		AdjTwo[u].push_back({ v, w });
	}
	for (int v = 0; v < N; ++v)
		Dijkstra(v);
	while (T--) {
		int v, u, p;
		scanf("%d %d %d", &v, &u, &p);
		int ans = dist[--v][--u][0];
		for (int i = 1; i <= p; ++i)
			ans = min(ans, dist[v][u][i]);
		ans == INF ? printf("IMPOSSIBLE\n") : printf("%d\n", ans);
	}
}