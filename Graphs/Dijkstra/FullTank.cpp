#include <iostream>
#include <vector>
#include <set>
#include <tuple>
#define INF 1e9
using namespace std;

int Dijsktra(vector<vector<pair<int, int>>>& Adj, vector<int>& P, int fuelCapacity, int s, int t)
{
	vector<vector<int>> dp(Adj.size(), vector<int>(fuelCapacity + 1));
	
	set<tuple<int, int, int>> Q;
	
	for (int v = 0; v < Adj.size(); ++v)
	{
		if (v != s)
		{
			dp[v][0] = INF;
			
			Q.insert(make_tuple(INF, v, 0));
		}
	}

	dp[s][0] = 0;
	
	Q.insert(make_tuple(0, s, 0));

	for (int currentFuel = 1; currentFuel <= fuelCapacity; ++currentFuel)
	{
		for (int v = 0; v < Adj.size(); ++v)
		{
			dp[v][currentFuel] = INF;
			
			Q.insert(make_tuple(INF, v, currentFuel));
		}
	}

	while (!Q.empty())
	{
		auto [_, v, currentFuel] = *Q.begin();
		Q.erase(Q.begin());

		if (currentFuel < fuelCapacity && dp[v][currentFuel] + P[v] < dp[v][currentFuel + 1])
		{
			Q.erase(make_tuple(dp[v][currentFuel + 1], v, currentFuel + 1));
			
			dp[v][currentFuel + 1] = dp[v][currentFuel] + P[v];
			
			Q.insert(make_tuple(dp[v][currentFuel + 1], v, currentFuel + 1));
		}

		for (auto [u, fuelNeeded] : Adj[v])
		{
			if (fuelNeeded <= currentFuel && dp[v][currentFuel] < dp[u][currentFuel - fuelNeeded])
			{
				Q.erase(make_tuple(dp[u][currentFuel - fuelNeeded], u, currentFuel - fuelNeeded));

				dp[u][currentFuel - fuelNeeded] = dp[v][currentFuel];

				Q.insert(make_tuple(dp[u][currentFuel - fuelNeeded], u, currentFuel - fuelNeeded));
			}
		}
	}
	
	return dp[t][0];
}

int main()
{
	int N;
	int M;

	cin >> N >> M;

	vector<int> P(N);

	for (int v = 0; v < N; ++v)
	{
		cin >> P[v];
	}

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

	int Q;

	cin >> Q;

	while (Q--)
	{
		int C;
		int S;
		int T;

		cin >> C >> S >> T;

		int res = Dijsktra(Adj, P, C, S, T);

		if (res == INF)
		{
			cout << "impossible" << endl;
		}
		else
		{
			cout << res << endl;
		}
	}
}