#include <iostream>
#include <vector>
#include <set>
#define INF 2e9
using namespace std;

int main()
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

		Adj[--v].push_back({ --u, w });
	}

	vector<int> D(N);
	set<pair<int, int>> Q;

	vector<int> C(N, 0);

	for (int v = 1; v < N; ++v)
	{
		D[v] = INF;
		Q.insert(make_pair(INF, v));
	}

	D[0] = 0;
	Q.insert(make_pair(0, 0));

	for (int i = 0; i < N - 1; ++i)
	{
		auto [_, v] = *Q.begin();
		Q.erase(Q.begin());

		for (auto [u, w] : Adj[v])
		{
			if (D[v] + w < D[u])
			{
				Q.erase(make_pair(D[u], u));
				D[u] = D[v] + w;
				Q.insert(make_pair(D[u], u));
				
				C[u] = 1;
			}
			else if (D[v] + w == D[u])
			{
				C[u] += 1;
			}
		}
	}

	int importantRoads = 0;
	int veryImportantRoads = 0;

	for (int v = 1; v < N; ++v)
	{
		importantRoads += C[v];

		if (C[v] == 1)
		{
			veryImportantRoads += 1;
		}
	}

	cout << importantRoads << " " << veryImportantRoads << endl;
}