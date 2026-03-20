#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#define MAXN 1000000
#define with 0
#define without 1
using namespace std;

vector<int> C(MAXN);
vector<vector<int>> Adj(MAXN);
vector<int> previsit(MAXN);
priority_queue<pair<int, int>> Q;
stack<pair<int, int>> S;
vector<vector<int>> dp(MAXN, vector<int>(2));
int N;

void DepthFirstSearch() {
	int currentTime = 1;
	previsit[0] = currentTime++;
	S.push({ 0, -1 });
	while (!S.empty()) {
		int v = S.top().first;
		int p = S.top().second;
		S.pop();
		for (int u : Adj[v]) {
			if (u != p) {
				previsit[u] = currentTime++;
				S.push({ u, v });
			}
		}
	}
}

int main() {
	freopen("schoolnet.in", "r", stdin);
	freopen("schoolnet.out", "w", stdout);
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
		scanf("%d", &C[i]);
	for (int i = 0; i < N - 1; ++i) {
		int v, u;
		scanf("%d %d", &v, &u);
		Adj[--v].push_back(--u);
		Adj[u].push_back(v);
	}
	DepthFirstSearch();
	for (int i = 0; i < N; ++i)
		Q.push({ previsit[i], i });
	while (!Q.empty()) {
		int v = Q.top().second;
		Q.pop();
		dp[v][with] = 0;
		dp[v][without] = C[v];
		for (int u : Adj[v]) {
			if (previsit[u] > previsit[v]) {
				dp[v][with] += dp[u][without];
				dp[v][without] += dp[u][with];
			}
		}
		dp[v][with] = min(dp[v][with], dp[v][without]);
	}
	printf("%d\n", dp[0][with]);
}