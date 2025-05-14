#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 1500
#define INF 2e9
using namespace std;

vector<vector<int>> A(MAXN + 1, vector<int>(MAXN + 1));
vector<vector<int>> PSH(MAXN + 1, vector<int>(MAXN + 1));
vector<vector<int>> PSV(MAXN + 1, vector<int>(MAXN + 1));
vector<vector<int>> dp(2, vector<int>(MAXN + 1));
int N;
int K;

int C(int i, int j) {
	return PSV[j - 1][j] - PSV[i - 1][j];
}

int main() {
	scanf("%d %d", &N, &K);
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N - i; ++j) {
			scanf("%d", &A[i][i + j]);
			PSH[i][i + j] = PSH[i][i + j - 1] + A[i][i + j];
		}
	}
	for (int j = 1; j <= N; ++j) {
		for (int i = 1; i <= N; ++i) {
			PSV[i][j] = PSV[i - 1][j] + A[i][j];
		}
	}
	dp[0][0] = 0;
	for (int i = 1; i <= N; ++i)
		dp[0][i] = INF;
	for (int j = 1; j <= K; ++j) {
		for (int i = 1; i <= N; ++i) {
			dp[j % 2][i] = INF;
			for (int k = 1; k <= i; ++k)
				dp[j % 2][i] = min(dp[j % 2][i], dp[(j - 1) % 2][k - 1] + C(k, i));
		}
	}
	printf("%d\n", dp[K % 2][N]);
}