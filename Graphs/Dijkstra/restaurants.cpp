#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#define MAXN 100000
#define MAXK 50
#define INF 1e12
using namespace std;

set<pair<long long, int>> Q;
vector<int> A(MAXN);
vector<vector<int>> I(MAXK);
vector<vector<pair<int, int>>> Adj(MAXN);
vector<vector<long long>> D(MAXK, vector<long long>(MAXN));
vector<long long> TD(MAXN);
int N;
int M;
int K;

void Dijkstra(int i) {
	for (int v = 0; v < N; ++v)
		D[i][v] = INF;
	for (int v : I[i]) {
		D[i][v] = 0;
		Q.insert({ 0, v });
	}
	while (!Q.empty()) {
		auto [d, v] = *Q.begin();
		Q.erase(Q.begin());
		if (d > D[i][v])
			continue;
		for (auto [u, w] : Adj[v]) {
			if (D[i][v] + w < D[i][u]) {
				D[i][u] = D[i][v] + w;
				Q.insert({ D[i][u], u });
			}
		}
	}
}

int main() {
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 0; i < N; ++i) {
		scanf("%d", &A[i]);
		I[--A[i]].push_back(i);
	}
	for (int i = 0; i < M; ++i) {
		int v, u, w;
		scanf("%d %d %d", &v, &u, &w);
		Adj[--v].push_back({ --u, w });
		Adj[u].push_back({ v, w });
	}
	for (int i = 0; i < K; ++i)
		Dijkstra(i);
	for (int v = 0; v < N; ++v)
		for (int i = 0; i < K; ++i)
			TD[v] += D[i][v];
	int optimalNode = 0;
	for (int v = 1; v < N; ++v)
		if (TD[v] < TD[optimalNode])
			optimalNode = v;
	printf("%d\n", optimalNode + 1);
}