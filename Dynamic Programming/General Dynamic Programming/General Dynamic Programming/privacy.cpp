#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 400
#define INF 2e9
using namespace std;

vector<int> A(MAXN + 1);
vector<vector<int>> C(MAXN + 1, vector<int>(MAXN + 1));
vector<vector<int>> dp(2, vector<int>(MAXN + 1, INF));
int N;
int K; 

int main() {
	scanf("%d %d", &N, &K);
	for (int i = 1; i <= N; ++i)
		scanf("%d", &A[i]);
	for (int i = 1; i <= N; ++i)
		for (int j = i; j <= N; ++j)
			for (int k = i; k <= j; ++k)
				C[i][j] += max(j - i - A[k], 0);
	for (int j = 0; j <= K - 1; ++j)
		dp[j % 2][0] = 0;
	for (int i = 1; i <= N; ++i)
		dp[0][i] = C[1][i];
	for (int j = 1; j <= K; ++j)
		for (int i = 1; i <= N; ++i)
			for (int k = 1; k <= i; ++k)
				dp[j % 2][i] = min(dp[j % 2][i], dp[(j - 1) % 2][k - 1] + C[k][i]);
	printf("%d\n", dp[K % 2][N]);
}