#include <iostream>
#include <vector>
#include <set>
#define INF 1e18
using namespace std;

int main()
{
	int N;
	int A;
	int B;
	int C;

	cin >> N >> A >> B >> C;

	vector<vector<int>> D(N, vector<int>(N));

	for (int v = 0; v < N; ++v)
	{
		for (int u = 0; u < N; ++u)
		{
			cin >> D[v][u];
		}
	}

	vector<long long> dp(2 * N);

	set<pair<long long, int>> Q;

	for (int v = 1; v < 2 * N; ++v)
	{
		dp[v] = INF;

		Q.insert(make_pair(dp[v], v));
	}

	dp[0] = 0;

	Q.insert(make_pair(dp[0], 0));

	for (int i = 0; i < 2 * N - 1; ++i)
	{
		auto [_, v] = *Q.begin();
		Q.erase(Q.begin());

		for (int u = 0; u < N; ++u)
		{
			if (v < N)
			{
				if (dp[v] + D[v][u] * A < dp[u ])
				{
					
				}
			}
		}
	}
}