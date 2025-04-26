#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cfloat>
#include <array>
#include <set>
#include <algorithm>
#define MAXN 150
#define MAXV 500
#define INF DBL_MAX
using namespace std;

set<array<double, 3>> Q;
vector<vector<array<int, 3>>> Adj(MAXN);
vector<vector<double>> dist(MAXN, vector<double>(MAXV + 1));
vector<vector<pair<int, int>>> parent(MAXN, vector<pair<int, int>>(MAXV + 1));
vector<int> path;
int N;
int M;
int D;

void Dijkstra(int maximumSpeedLimit) {
	for (int v = 0; v < N; ++v)
		for (int speedLimit = 1; speedLimit <= maximumSpeedLimit; ++speedLimit)
			dist[v][speedLimit] = INF;
	parent[0][70] = { 0, 70 };
	dist[0][70] = 0;
	Q.insert({ 0,  0,  70 });
	while (!Q.empty()) {
		double d = (*Q.begin())[0];
		int v = (int)(*Q.begin())[1];
		int currentSpeed = (int)(*Q.begin())[2];
		Q.erase(Q.begin());
		for (auto adjacent : Adj[v]) {
			int u = adjacent[0];
			int newSpeed = adjacent[1] != 0 ? adjacent[1] : currentSpeed;
			int length = adjacent[2];
			if (dist[v][currentSpeed] + (double)length / newSpeed < dist[u][newSpeed]) {
				parent[u][newSpeed] = { v, currentSpeed };
				dist[u][newSpeed] = dist[v][currentSpeed] + (double)length / newSpeed;
				Q.insert({ dist[u][newSpeed], (double) u, (double) newSpeed });
			}
		}
	}
}

int main() {
	scanf("%d %d %d", &N, &M, &D);
	int maximumSpeedLimit = 0;
	for (int i = 0; i < M; ++i) {
		int v, u, s, l;
		scanf("%d %d %d %d", &v, &u, &s, &l);
		Adj[v].push_back({ u, s, l });
		maximumSpeedLimit = max(maximumSpeedLimit, s);
	}
	Dijkstra(maximumSpeedLimit);
	int optimalSpeedLimit = 1;
	for (int speedLimit = 2; speedLimit <= maximumSpeedLimit; ++speedLimit)
		if (dist[D][speedLimit] < dist[D][optimalSpeedLimit])
			optimalSpeedLimit = speedLimit;
	int v = D;
	int speedLimit = optimalSpeedLimit;
	while (v != 0) {
		path.push_back(v);
		int u = v;
		v = parent[u][speedLimit].first;
		speedLimit = parent[u][speedLimit].second;
	}
	path.push_back(v);
	reverse(path.begin(), path.end());
	for (int v : path)
		printf("%d ", v);
}