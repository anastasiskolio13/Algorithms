#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <numeric>
#define MAXN 60000
#define MAXK MAXN
#define MAXB MAXN
#define INF 1e18
using namespace std;

set<pair<int, int>> Z;
set<pair<long long, int>> Q;
vector<vector<pair<int, int>>> Adj(MAXN);
vector<int> P(MAXK);
vector<int> G(MAXB);
vector<long long> dist(MAXN);
vector<long long> S;
int N;
int M;
int K;
int L;
int B;

void Dijkstra() {
	for (int v = 0; v < N; ++v)
		dist[v] = INF;
	for (int i = 0; i < B; ++i) {
		dist[--G[i]] = 0;
		Q.insert({ 0, G[i] });
	}
	while (!Q.empty()) {
		auto [d, v] = *Q.begin();
		Q.erase(Q.begin());
		if (d > dist[v])
			continue;
		for (auto [u, w] : Adj[v]) {
			if (dist[v] + w < dist[u]) {
				dist[u] = dist[v] + w;
				Q.insert({ dist[u], u });
			}
		}
	}
}

int main() {
	scanf("%d %d %d %d %d", &N, &M, &K, &L, &B);
	for (int i = 0; i < M; ++i) {
		int v, u, w;
		scanf("%d %d %d", &v, &u, &w);
		Adj[--v].push_back({ --u, w });
		Adj[u].push_back({ v, w });
	}
	scanf("%d", &P[0]);
	for (int i = 1; i < K; ++i) {
		scanf("%d", &P[i]);
		Z.insert({ P[i - 1] - 1, P[i] - 1 });
	}
	for (int i = 0; i < B; ++i)
		scanf("%d", &G[i]);
	long long costOfPath = 0;
	for (int v = 0; v < Adj.size(); ++v) {
		for (auto [u, w] : Adj[v]) {
			if (Z.find({ v, u }) != Z.end()) {
				costOfPath += w;
				Z.erase({ v, u });
			}
		}
	}
	Dijkstra();
	for (int i = 1; i < K - 1; ++i)
		S.push_back(dist[--P[i]]);
	sort(S.begin(), S.end());
	printf("%lld\n", costOfPath + accumulate(S.begin(), S.begin() + L, 0));
}