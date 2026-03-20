#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <array>
#include <climits>
#include <set>
#include <array>
#define MAXN 2000
#define MAXK 200
#define INF LONG_MAX
using namespace std;

set<array<long, 3>> Q;
vector<vector<array<int, 3>>> Adj(MAXN);
vector<vector<long>> dist(MAXN, vector<long>(MAXK));
int K;
int N;
int M;
int A;
int B;

void Dijkstra() {
	for (int v = 0; v < N; ++v)
		for (int hullDamage = 0; hullDamage < K; ++hullDamage)
			dist[v][hullDamage] = INF;
	dist[A][0] = 0;
	Q.insert({ 0, A, 0 });
	while (!Q.empty()) {
		long d = (*Q.begin())[0];
		int v = (int)(*Q.begin())[1];
		int hullDamage = (int)(*Q.begin())[2];
		Q.erase(Q.begin());
		for (auto adjacent : Adj[v]) {
			int u = adjacent[0];
			int w = adjacent[1];
			int damage = adjacent[2];
			if (hullDamage + damage < K && dist[v][hullDamage] + w < dist[u][hullDamage + damage]) {
				dist[u][hullDamage + damage] = dist[v][hullDamage] + w;
				Q.insert({ dist[u][hullDamage + damage], u, hullDamage + damage });
			}
		}
	}
}

int main() {
	scanf("%d %d %d", &K, &N, &M);
	for (int i = 0; i < M; ++i) {
		int a, b, t, h;
		scanf("%d %d %d %d", &a, &b, &t, &h);
		Adj[--a].push_back({ --b, t, h });
		Adj[b].push_back({ a, t, h });
	}
	scanf("%d %d", &A, &B);
	--A;
	--B;
	Dijkstra();
	long minimumDistance = dist[B][0];
	for (int hullDamage = 1; hullDamage < K; ++hullDamage)
		minimumDistance = min(minimumDistance, dist[B][hullDamage]);
	printf("%ld\n", minimumDistance == INF ? -1 : minimumDistance);
}