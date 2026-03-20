#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 500
#define INF 2e9
using namespace std;

vector<int> A(MAXN + 1);
vector<int> PSW(MAXN + 1);
vector<int> PSB(MAXN + 1);
vector<vector<int>> dp(2, vector<int>(MAXN + 1));
int N;
int K;

int C(int i, int j) {
	return (PSW[j] - PSW[i - 1]) * (PSB[j] - PSB[i - 1]);
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
		scanf("%d", &A[i]);
		PSW[i] = PSW[i - 1] + !A[i];
		PSB[i] = PSB[i - 1] + (A[i] == 1);
	}
	dp[0][0] = 0;
	for (int i = 1; i <= N; ++i)
		dp[0][i] = INF;
	for (int j = 1; j <= K; ++j)
		ComputeDP(j, 1, N, 1, N);
	printf("%d\n", dp[K % 2][N]);
}