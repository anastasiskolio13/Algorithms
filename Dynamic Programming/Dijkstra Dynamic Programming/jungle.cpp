#include <iostream>
#include <vector>
#include <set>
#include <tuple>
#define INF 1e18
using namespace std;

int main()
{
	int N;
	int M;
	int K;

	scanf("%d %d %d", &N, &M, &K);

	vector<vector<pair<int, int>>> Adj(N);

	for (int i = 0; i < M; ++i)
	{
		int v;
		int u;
		int w;

		scanf("%d %d %d", &v, &u, &w);

		Adj[--v].push_back(make_pair(--u, w));
		Adj[u].push_back(make_pair(v, w));
	}
	
	vector<vector<long long>> D(N, vector<long long>(K + 1));
	set<tuple<long long, int, int>> Q;

	for (int k = 0; k <= K; ++k)
	{
		D[0][k] = 0;
		Q.insert(make_tuple(0, 0, k));

		for (int v = 1; v < N; ++v)
		{
			D[v][k] = INF;
			Q.insert(make_tuple(INF, v, k));
		}
	}

	while (!Q.empty())
	{
		auto [_, v, k] = *Q.begin();
		Q.erase(Q.begin());

		for (auto [u, w] : Adj[v])
		{
			if (D[v][k] + w < D[u][k])
			{
				Q.erase(make_tuple(D[u][k], u, k));
				D[u][k] = D[v][k] + w;
				Q.insert(make_tuple(D[u][k], u, k));
			}

			if (k < K && D[v][k] < D[u][k + 1])
			{
				Q.erase(make_tuple(D[u][k + 1], u, k + 1));
				D[u][k + 1] = D[v][k];
				Q.insert(make_tuple(D[u][k + 1], u, k + 1));
			}
		}
	}

	printf("%lld\n", D[N - 1][K] != INF ? D[N - 1][K] : -1);
}