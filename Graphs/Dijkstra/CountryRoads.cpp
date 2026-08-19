#include <iostream>
#include <vector>
#include <set>
#define INF 1e9
using namespace std;

int main()
{
	int T;

	cin >> T;

	for (int caseNumber = 1; caseNumber <= T; ++caseNumber)
	{
		int N;
		int M;

		cin >> N >> M;

		vector<vector<pair<int, int>>> Adj(N);

		for (int i = 0; i < M; ++i)
		{
			int v;
			int u;
			int w;

			cin >> v >> u >> w;

			Adj[v].push_back(make_pair(u, w));
			Adj[u].push_back(make_pair(v, w));
		}

		int S;

		cin >> S;

		vector<int> D(N);

		set<pair<int, int>> Q;

		for (int v = 0; v < N; ++v)
		{
			if (v != S)
			{
				D[v] = INF;

				Q.insert(make_pair(INF, v));
			}
		}

		D[S] = 0;

		Q.insert(make_pair(0, S));

		for (int i = 0; i < N - 1; ++i)
		{
			auto [_, v] = *Q.begin();
			Q.erase(Q.begin());

			for (auto [u, w] : Adj[v])
			{
				if (max(D[v], w) < D[u])
				{
					Q.erase(make_pair(D[u], u));

					D[u] = max(D[v], w);

					Q.insert(make_pair(D[u], u));
				}
			}
		}

		cout << "Case " << caseNumber << ":" << endl;

		for (int v = 0; v < N; ++v)
		{
			if (D[v] == INF)
			{
				cout << "Impossible" << endl;
			}
			else
			{
				cout << D[v] << endl;
			}
		}
	}
}