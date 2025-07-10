#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 20
#define INF 1e9
using namespace std;

vector<vector<int>> A(MAXN, vector<int>(MAXN));
vector<vector<int>> dp(1 << MAXN, vector<int>(MAXN));
int N;

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			scanf("%d", &A[i][j]);
	for (int i = 0; i < N; ++i)
		dp[0][i] = 0;
	for (int s = 1; s < (1 << N); ++s) {
		for (int i = 0; i < N; ++i) {
			dp[s][i] = INF;
			for (int j = 0; j < N; ++j)
				if (j != i && s & (1 << j))
					dp[s][i] = min(dp[s][i], dp[s & ~(1 << j)][j] + A[i][j]);
		}
	}
	int minimumCost = INF;
	for (int i = 0; i < N; ++i)
		minimumCost = min(minimumCost, dp[(1 << N) & ~(1 << i)][i]);
	printf("%d\n", 2 * minimumCost);
}