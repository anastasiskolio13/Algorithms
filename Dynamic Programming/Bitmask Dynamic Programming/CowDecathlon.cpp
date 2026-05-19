#include <iostream>
#include <vector>
#define INF 2e9
using namespace std;

int main()
{
	int N;
	int M;

	cin >> N >> M;

	vector<vector<pair<int, int>>> B(N + 1);

	for (int i = 0; i < M; ++i)
	{
		int Ki;
		int Pi;
		int Ai;

		cin >> Ki >> Pi >> Ai;

		B[Ki].push_back(make_pair(Pi, Ai));
	}

	vector<vector<int>> S(N, vector<int>(N));

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			cin >> S[i][j];
		}
	}

	vector<int> dp(1 << N, INF);

	dp[0] = 0;

	for (int s = 1; s < 1 << N; ++s)
	{
		int subsetSize = popcount(static_cast<unsigned int>(s));

		for (int i = 0; i < N; ++i)
		{
			if (s & (1 << i))
			{
				dp[s] = max(dp[s], dp[s & ~(1 << i)] + S[i][j]);
			}
		}
	}
}