#include <iostream>
#include <vector>
#define INF 2e9
using namespace std;

int main()
{
	int N;
	int X;
	int Y;

	cin >> N >> X >> Y;

	vector<int> A(N + 1);
	vector<int> B(N + 1);

	for (int i = 1; i <= N; ++i)
	{
		cin >> A[i] >> B[i];
	}

	vector<vector<vector<int>>> dp(2, vector<vector<int>>(N + 1, vector<int>(Y + 1)));

	for (int y = 0; y <= Y; ++y)
	{
		dp[0][0][y] = 0;
	}

	for (int j = 1; j <= N; ++j)
	{
		for (int y = 0; y <= Y; ++y)
		{
			dp[0][j][y] = INF;
		}
	}

	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= N; ++j)
		{
			for (int y = 0; y <= Y; ++y)
			{
				dp[i % 2][j][y] = dp[(i - 1) % 2][j][y];

				if (B[i] <= y)
				{
					dp[i % 2][j][y] = min(dp[i % 2][j][y], dp[(i - 1) % 2][j - 1][y - B[i]] + A[i]);
				}
			}
		}
	}

	for (int i = N; i >= 0; --i)
	{
		if (dp[N % 2][i][Y] <= X)
		{
			cout << i + (i < N) << "\n";
			return 0;
		}
	}
}