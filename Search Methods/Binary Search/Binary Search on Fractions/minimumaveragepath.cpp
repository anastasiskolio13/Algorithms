#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 100000
#define eps 1e-6
#define INF 1e14
using namespace std;

vector<vector<pair<int, int>>> Adj(MAXN);
vector<double> dp(MAXN);
vector<int> P(MAXN);
vector<int> path;
int N;
int M;

double ShortestPathInDag(double L) {
	fill(dp.begin(), dp.begin() + N - 1, INF);
	dp[N - 1] = 0;
	P[N - 1] = N - 1;
	for (int v = N - 2; v >= 0; --v) {
		for (auto adjacent : Adj[v]) {
			int u = adjacent.first;
			double w = adjacent.second - L;
			if (dp[u] + w < dp[v]) {
				dp[v] = dp[u] + w;
				P[v] = u;
			}
		}
	}
	return dp[0];
}

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; ++i) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		Adj[--a].push_back({ --b, c });
	}
	double lo = 0;
	double hi = 1e14;
	while (hi - lo > eps) {
		double mid = (lo + hi) / 2;
		if (ShortestPathInDag(mid) <= 0)
			hi = mid;
		else
			lo = mid;
	}
	int v = 0;
	while (v != P[v]) {
		path.push_back(v + 1);
		v = P[v];
	}
	path.push_back(N);
	printf("%d\n", path.size() - 1);
	for (int v : path)
		printf("%d ", v);
}