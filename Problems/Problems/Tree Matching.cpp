#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#define MAXN 200000
#define with 0
#define without 1
using namespace std;

vector<vector<int>> Adj(MAXN);
vector<int> previsit(MAXN);
stack<pair<int, int>> S;
priority_queue<pair<int, int>> Q;
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
	scanf("%d", &N);
	for (int i = 0; i < N - 1; ++i) {
		int v, u;
		scanf("%d %d", &v, &u);
		Adj[--v].push_back(--u);
		Adj[u].push_back(v);
	}
	DepthFirstSearch();
	for (int v = 0; v < N; ++v)
		Q.push({ previsit[v], v });
	while (!Q.empty()) {
		int v = Q.top().second;
		Q.pop();
		int sumWithout = 0;
		for (int u : Adj[v])
			sumWithout += (dp[u][without]) * (previsit[u] > previsit[v]);
		dp[v][without] = dp[v][with] = sumWithout;
		for (int u : Adj[v])
			dp[v][without] = max(dp[v][without], (sumWithout - dp[u][without] + dp[u][with] + 1) * (previsit[u] > previsit[v]));
	}
	printf("%d\n", dp[0][without]);
}