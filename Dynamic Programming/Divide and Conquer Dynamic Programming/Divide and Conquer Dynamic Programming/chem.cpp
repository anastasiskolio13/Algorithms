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
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N - i; ++j) {
			scanf("%d", &A[i][i + j]);
			PSH[i][i + j] = PSH[i][i + j - 1] + A[i][i + j];
		}
	}
	for (int j = 1; j <= N; ++j) {
		for (int i = 1; i <= N; ++i) {
			PSV[i][j] = PSV[i - 1][j] + PSH[i][j];
		}
	}
	dp[0][0] = 0;
	for (int i = 1; i <= N; ++i)
		dp[0][i] = INF;
	for (int j = 1; j <= K; ++j)
		ComputeDP(j, 1, N, 1, N);
	printf("%d\n", dp[K % 2][N]);
}