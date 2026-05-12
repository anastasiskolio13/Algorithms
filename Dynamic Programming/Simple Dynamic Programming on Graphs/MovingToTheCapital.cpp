#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define INF 100001
using namespace std;

int main()
{
	int T;

	cin >> T;
	
	while (T--)
	{
		int N;
		int M;

		cin >> N >> M;

		vector<vector<int>> Adj(N);

		for (int i = 0; i < M; ++i)
		{
			int v;
			int u;

			cin >> v >> u;

			Adj[--v].push_back(--u);
		}

		vector<int> D(N, INF);
		queue<int> Q;

		D[0] = 0;
		Q.push(0);

		while (!Q.empty())
		{
			int v = Q.front();
			Q.pop();

			for (int u : Adj[v])
			{
				if (D[u] == INF)
				{
					D[u] = D[v] + 1;
					Q.push(u);
				}
			}
		}

		vector<pair<int, int>> I(N);

		for (int i = 0; i < N; ++i)
		{
			I[i] = make_pair(D[i], i);
		}

		sort(I.begin(), I.begin() + N, greater<pair<int, int>>());

		vector<int> dp(N);
	
		//tex:
		//$ 
		// dp[v] = \min
		//		\begin{cases}
		//			\min_{ u \in Adj(v) }\left\{D[u] : D[u] \leq D[v]\right\}, \\
		//			\min_{ u \in Adj(v) }\left\{dp[u] : D[u] > D[v]\right\}.
		//		\end{cases}
		//$

		for (auto [_, v] : I)
		{
			dp[v] = D[v];
			int minimumDistance = D[v];

			for (int u : Adj[v])
			{
				if (D[u] <= D[v])
				{
					minimumDistance = min(minimumDistance, D[u]);
					dp[v] = min(dp[v], minimumDistance);
				}
				else
				{
					dp[v] = min(dp[v], dp[u]);
				}
			}
		}

		for (int i = 0; i < N; ++i)
		{
			cout << dp[i] << " ";
		}

		cout << endl;
	}
}