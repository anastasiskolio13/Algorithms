#include <iostream>
#include <vector>
#include <set>
#define INF 2e9
using namespace std;

long long calculateSumOfCows(int v, vector<vector<int>>& Adj, vector<int>& C, vector<long long>& sumOfCows)
{
	sumOfCows[v] = C[v];

	for (int u : Adj[v])
	{
		sumOfCows[v] += calculateSumOfCows(u, Adj, C, sumOfCows);
	}

	return sumOfCows[v];
}

int main()
{
	freopen("shortcut.in", "r", stdin);
	freopen("shortcut.out", "w", stdout);

	int N;
	int M;
	int T;

	cin >> N >> M >> T;

	vector<int> C(N);

	for (int i = 0; i < N; ++i)
	{
		cin >> C[i];
	}

	vector<vector<pair<int, int>>> Adj(N);

	for (int i = 0; i < M; ++i)
	{
		int v;
		int u;
		int w;

		cin >> v >> u >> w;

		Adj[--v].push_back(make_pair(--u, w));
		Adj[u].push_back(make_pair(v, w));
	}

	vector<int> D(N);
	vector<int> P(N);
	set<pair<int, int>> Q;

	for (int i = 1; i < N; ++i)
	{
		D[i] = INF;
		Q.insert(make_pair(D[i], i));
	}

	D[0] = 0;
	Q.insert(make_pair(D[0], 0));

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
				P[u] = v;
			}
			else if (D[v] + w == D[u] && v < P[u])
			{
				P[u] = v;
			}
		}
	}

	vector<vector<int>> AdjT(N);

	for (int i = 1; i < N; ++i)
	{
		AdjT[P[i]].push_back(i);
	}

	vector<long long> sumOfCows(N);

	calculateSumOfCows(0, AdjT, C, sumOfCows);

	long long maximumDecrease = 0;

	for (int i = 1; i < N; ++i)
	{
		long long currentDecrease = max(0LL, (D[i] - T) * sumOfCows[i]);
		maximumDecrease = max(maximumDecrease, currentDecrease);
	}

	cout << maximumDecrease << endl;
}