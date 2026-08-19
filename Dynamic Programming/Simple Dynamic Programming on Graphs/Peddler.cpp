#include <iostream>
#include <vector>
#include <algorithm>
#define INF 1e9
using namespace std;

int main()
{
	int N;
	int M;

	cin >> N >> M;

	vector<int> A(N);

	for (int v = 0; v < N; ++v)
	{
		cin >> A[v];
	}

	vector<vector<int>> Adj(N);

	for (int i = 0; i < M; ++i)
	{
		int v;
		int u;

		cin >> v >> u;

		Adj[--v].push_back(--u);
	}

	vector<vector<int>> dp(N, vector<int>(2));

	for (int v = N - 1; v >= 0; --v)
	{
		dp[v][0] = -INF;
		dp[v][1] = A[v];

		for (int u : Adj[v])
		{
			dp[v][0] = max({ dp[v][0], dp[u][1] - A[v], dp[u][0] });
			dp[v][1] = max({ dp[v][1], dp[u][1] });
		}
	}

	int maximumProfit = -INF;

	for (int v = 0; v < N; ++v)
	{
		maximumProfit = max(maximumProfit, dp[v][0]);
	}

	cout << maximumProfit << endl;
}