#include <iostream>
#include <vector>
#include <set>
#include <stack>
#define INF 2e9
using namespace std;

int main()
{
	int N;
	int M;
	int K;
	int S;
	int T;

	cin >> N >> M >> K >> S >> T;

	--S;
	--T;

	vector<vector<pair<int, int>>> Adj(N);

	for (int i = 0; i < M; ++i)
	{
		int v;
		int u;
		int w;

		cin >> v >> u >> w;

		Adj[--v].push_back(make_pair(--u, w));
	}

	vector<int> D(N);
	set<pair<int, int>> Q;

	for (int v = 0; v < N; ++v)
	{
		if (v != S)
		{
			D[v] = INF;
			Q.insert(make_pair(D[v], v));
		}
	}

	D[S] = 0;
	Q.insert(make_pair(D[S], S));

	vector<vector<int>> AdjR(N);

	while (!Q.empty())
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
				AdjR[u] = { v };
			}
			else if (D[v] + w == D[u])
			{
				AdjR[u].push_back(v);
			}
		}
	}

	vector<bool> isContainedInAShortestPath(N, false);
	stack<int> Z;

	isContainedInAShortestPath[T] = true;
	Z.push(T);

	while (!Z.empty())
	{
		int v = Z.top();
		Z.pop();

		for (int u : AdjR[v])
		{
			if (!isContainedInAShortestPath[u])
			{
				isContainedInAShortestPath[u] = true;
				Z.push(u);
			}
		}
	}

	int ans = D[T];

	while (K--)
	{
		int v;
		int u; 
		int w;

		cin >> v >> u >> w;

		if (D[--v] != INF && isContainedInAShortestPath[--u])
		{
			ans = min(ans, D[v] + w + D[T] - D[u]);
		}
	}

	cout << ans << endl;
}