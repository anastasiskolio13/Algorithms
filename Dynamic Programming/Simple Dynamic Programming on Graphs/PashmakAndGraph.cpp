#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
using namespace std;

int main()
{
	int N;
	int M; 

	scanf("%d %d", &N, &M);

	vector<vector<int>> Adj(N);
	vector<array<int, 3>> E(M);

	for (int i = 0; i < M; ++i)
	{
		scanf("%d %d %d", &E[i][0], &E[i][1], &E[i][2]);
		--E[i][0];
		--E[i][1];
	}

	//sort(E.begin(), E.end(), [](const array<int, 3>& A, const array<int, 3>& B) { return A[2] > B[2]; });

	vector<vector<array<int, 3>>> S(1e5 + 1);

	for (int i = 0; i < M; ++i)
	{
		S[E[i][2]].push_back(E[i]);
	}
	
	for (int i = 1e5, j = 0; i >= 1; i--)
	{
		int k = 0;
		
		while (k < S[i].size())
		{
			E[j++] = S[i][k++];
		}
	}


	for (int i = 0; i < M; ++i)
	{
		Adj[E[i][0]].push_back(i);
	}

	//tex:
	// $
	// dp[i] = 1 + \max
	// \begin{cases}
	//		\max_{j \in Adj(u_i)}\left\{ dp[j] : w_j > w_i \right\}, \\
	//		0.
	// \end{cases}
	// $

	vector<int> dp(M, 0);
	
	vector<int> P(N, 0);
	
	vector<int> I(N, 0);

	for (int i = 0; i < M; ++i)
	{
		auto [_, u, w] = E[i];

		while (P[u] < Adj[u].size() && E[Adj[u][P[u]]][2] > w)
		{
			if (dp[Adj[u][P[u]]] > dp[I[u]])
			{
				I[u] = Adj[u][P[u]];
			}

			++P[u];
		}

		dp[i] = dp[I[u]] * (P[u] > 0) + 1;
	}

	printf("%d\n", *max_element(dp.begin(), dp.end()));
}