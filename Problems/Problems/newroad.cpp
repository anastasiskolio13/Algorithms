#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#include <climits>
#include <array>
#define MAXN 10000
#define INF INT_MAX
using namespace std;

set<array<int, 3>> Q;
set<array<int, 3>> S;
vector<vector<pair<int, int>>> Adj(MAXN);
vector<vector<int>> dist(MAXN, vector<int>(2));
int N;
int M;
int K;
int s;
int t;

void Dijkstra() {
	for (int v = 0; v < N; ++v)
		dist[v][0] = dist[v][1] = INF;
	dist[s][0] = 0;
	Q.insert({ 0, s, 0 });
	while (!Q.empty()) {
		int w = (*Q.begin())[0];
		int v = (*Q.begin())[1];
		// Έχω χρησιμοποιήσει ήδη μία από τις επιπρόσθετες ακμές;
		int flag = (*Q.begin())[2]; 
		Q.erase(Q.begin());
		for (auto adjacent : Adj[v]) {
			int u = adjacent.first;
			int w = adjacent.second;
			if (S.find({ v, u, w }) != S.end()) {
				if (!flag) {
					if (dist[v][0] + w < dist[u][1]) {
						dist[u][1] = dist[v][0] + w;
						Q.insert({ dist[u][1], u, 1});
					}
				}
			}
			else {
				if (dist[v][flag] + w < dist[u][flag]) {
					dist[u][flag] = dist[v][flag] + w;
					Q.insert({ dist[u][flag], u, flag});
				}
			}
		}
	}
}

int main() {
	scanf("%d %d %d %d %d", &N, &M, &K, &s, &t);
	--s; --t;
	for (int i = 0; i < M + K; ++i) {
		int v, u, w;
		scanf("%d %d %d", &v, &u, &w);
		Adj[--v].push_back({ --u, w });
		if (i >= M) 
			S.insert({ v, u, w });
	}
	Dijkstra();
	printf("%d\n", dist[t][1]);
}