#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#include <array>
#include <climits>
#define MAXN 60000
#define INF LONG_MAX
using namespace std;

set<array<long, 3>> Q;
vector<vector<pair<int, int>>> Adj(MAXN);
vector<long> dist(MAXN);
int N;
int M;
int s;
int t;
int p;
int q;

void Relax(int v, int u, int w, int flag) {
	if (dist[v] + w < dist[u] || dist[v] + w >= dist[u] && ) {
		dist[u] = dist[v] + w;
		Q.insert({ dist[u], u, flag });
	}
}

void Dijkstra() {
	for (int v = 0; v < N; ++v)
		dist[v] = INF;
	dist[s] = 0;
	Q.insert({ 0, s, 0 });
	while (!Q.empty()) {
		long d = (*Q.begin())[0];
		int v = (int)(*Q.begin())[1];
		int flag = v == p ? 1 : (int)(*Q.begin())[2];
		Q.erase(Q.begin());
		for (auto adjacent : Adj[v]) {
			int u = adjacent.first;
			int w = adjacent.second;
			if ((u == q && flag) || (u != q)) 
				Relax(v, u, w, flag);
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
	//for (int i = 0; i < N; ++i)
		//cout << dist[i] << " ";
	printf("%ld\n", dist[t]);
}