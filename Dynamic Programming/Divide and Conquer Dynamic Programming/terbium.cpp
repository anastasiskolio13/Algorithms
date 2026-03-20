#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 5000
#define INF 1e18
using namespace std;

vector<int> X(MAXN + 1);
vector<int> W(MAXN + 1);
vector<long long> PSW(MAXN + 1);
vector<long long> PSXW(MAXN + 1);
vector<vector<long long>> dp(2, vector<long long>(MAXN + 1));
int N;
int K;

long long C(int i, int j) {
	return X[j] * (PSW[j] - PSW[i - 1]) - (PSXW[j] - PSXW[i - 1]);
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
		scanf("%d %d", &X[i], &W[i]);
		PSW[i] = PSW[i - 1] + W[i];
		PSXW[i] = PSXW[i - 1] + (long long)X[i] * W[i];
	}
	for (int j = 1; j <= K; ++j)
		dp[j % 2][1] = 0;
	for (int i = 2; i <= N; ++i)
		dp[1][i] = C(1, i);
	for (int j = 2; j <= K; ++j)
		ComputeDP(j, 2, N, 2, N);
	printf("%lld\n", dp[K % 2][N]);
}