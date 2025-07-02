#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 5000
#define INF 2e9
using namespace std;

int H[MAXN + 1];
int U[MAXN + 1][MAXN + 1];
int PSR[MAXN + 1][MAXN + 1];
int PSC[MAXN + 1][MAXN + 1];
int dp[2][MAXN + 1];
int N;
int K;

int C(int i, int j) {
	return PSC[j][N] - PSC[i][N] - PSC[j][i - 1] + PSC[i][i - 1];
}

void ComputeDP(int j, int lo, int hi, int opt_lo, int opt_hi) {
	if (lo > hi)
		return;
	int mid = (lo + hi) / 2;
	dp[j % 2][mid] = INF;
	int opt_i;
	for (int i = opt_lo; i <= min(opt_hi, mid); ++i) {
		if (dp[(j - 1) % 2][i - 1] + C(i, mid) < dp[j % 2][mid]) {
			dp[j % 2][mid] = dp[(j - 1) % 2][i - 1] + C(i, mid);
			opt_i = i;
		}
	}
	ComputeDP(j, lo, mid - 1, opt_lo, opt_i);
	ComputeDP(j, mid + 1, hi, opt_i, opt_hi);
}

int main() {
	scanf("%d %d", &N, &K);
	for (int i = 1; i <= N; ++i) 
		scanf("%d", &H[i]);
	for (int i = 2; i <= N; ++i)
		for (int j = 1; j < i; ++j)
			U[i][j] += H[j] > H[i];
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= N; ++j)
			PSR[i][j] = PSR[i][j - 1] + U[i][j];
	for (int j = 1; j <= N; ++j)
		for (int i = 1; i <= N; ++i)
			PSC[i][j] = PSC[i - 1][j] + PSR[i][j];
	for (int i = 1; i <= N; ++i)
		dp[1][i] = C(1, i);
	for (int j = 2; j <= K; ++j)
		dp[j % 2][1] = 0;
	for (int j = 2; j <= K; ++j)
		ComputeDP(j, 2, N, 2, N);
	printf("%d\n", dp[K % 2][N]);
}