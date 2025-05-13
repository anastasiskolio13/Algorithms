#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 20000
#define INF 1e14
using namespace std;

vector<int> W(MAXN + 1);
vector<int> D(MAXN + 1);
vector<long long> PSW(MAXN + 1);
vector<long long> PSD(MAXN + 1);
vector<long long> PSC(MAXN + 1);
vector<vector<long long>> dp(2, vector<long long>(MAXN + 2));
int N;

int C(int i, int j) {
	return PSD[j - 1] * (PSW[j - 1] - PSW[i - 1]) - PSC[j - 1] + PSC[i - 1];
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
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) {
		scanf("%d %d", &W[i], &D[i]);
		PSW[i] = PSW[i - 1] + W[i];
		PSD[i] = PSD[i - 1] + D[i];
		PSC[i] = PSC[i - 1] + W[i] * PSD[i - 1];
	}
	dp[0][0] = 0;
	for (int i = 1; i <= N + 1; ++i)
		dp[0][i] = INF;
	for (int j = 1; j <= 3; ++j)
		ComputeDP(j, 1, N + 1, 1, N + 1);
	printf("%lld\n", dp[1][N + 1]);
}