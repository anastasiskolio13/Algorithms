#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cfloat>
#include <array>
#include <set>
#include <algorithm>
#define MAXN 150
#define INF DBL_MAX
using namespace std;

set<array<double, 3>> Q;
vector<vector<array<int, 3>>> Adj(MAXN);
vector<double> dist(MAXN);
vector<int> parent(MAXN);
vector<int> path;
int N;
int M;
int D;

void Dijkstra() {
	for (int v = 0; v < N; ++v)
		dist[v] = INF;
	dist[0] = 0;
	parent[0] = 0;
	Q.insert({(double) 0, (double) 0, (double) 70 });
	while (!Q.empty()) {
		double d = (*Q.begin())[0];
		int v = (int)(*Q.begin())[1];
		int currentSpeed = (int)(*Q.begin())[2];
		Q.erase(Q.begin());
		for (auto adjacent : Adj[v]) {
			int u = adjacent[0];
			int newSpeed = adjacent[1] != 0 ? adjacent[1] : currentSpeed;
			int length = adjacent[2];
			if (dist[v] + (double)length / newSpeed < dist[u]) {
				dist[u] = dist[v] + (double)length / newSpeed;
				parent[u] = v;
				Q.insert({ dist[u], (double) u, (double) newSpeed });
			}
		}
	}
}

int main() {
	scanf("%d %d %d", &N, &M, &D);
	for (int i = 0; i < M; ++i) {
		int v, u, s, l;
		scanf("%d %d %d %d", &v, &u, &s, &l);
		Adj[v].push_back({ u, s, l });
	}
	Dijkstra();
	int v = D;
	while (v != parent[v]) {
		path.push_back(v);
		v = parent[v];
	}
	path.push_back(0);
	reverse(path.begin(), path.end());
	for (int v : path)
		printf("%d ", v);
}