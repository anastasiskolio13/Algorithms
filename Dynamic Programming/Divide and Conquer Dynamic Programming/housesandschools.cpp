#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 3000
#define INF 1e18
using namespace std;

vector<int> A(MAXN + 1);
vector<pair<long long, long long>> PS(MAXN + 1);
vector<vector<long long>> dp(2, vector<long long>(MAXN + 1));
int N;
int K;

long long C(int i, int j) {
	int mid = (i + j) / 2;
	return PS[mid].second - PS[i - 1].second - i * (PS[mid].first - PS[i - 1].first) + j * (PS[j].first - PS[mid].first) - PS[j].second + PS[mid].second;
}

void ComputeDP(int j, int lo, int hi, int opt_lo, int opt_hi) {
	if (lo > hi)
		return;
	int mid = (lo + hi) / 2;
	dp[j % 2][mid] = INF;
	int opt_i;
	for (int i = opt_lo; i <= min(opt_hi, mid); ++i) {
		if (dp[(j - 1) % 2][i] + C(i, mid) < dp[j % 2][mid]) {
			dp[j % 2][mid] = dp[(j - 1) % 2][i] + C(i, mid);
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
		PS[i].first = PS[i - 1].first + A[i];
		PS[i].second = PS[i - 1].second + (long long)A[i] * i;
	}
	for (int i = 1; i <= N; ++i)
		dp[0][i] = i * PS[i].first - PS[i].second;
	for (int j = 1; j <= K - 1; ++j) 
		ComputeDP(j, 1, N, 1, N);
	long long optimalDP = INF;
	for (int i = 1; i <= N; ++i)
		optimalDP = min(optimalDP, dp[(K - 1) % 2][i] + PS[N].second - PS[i - 1].second - i * (PS[N].first - PS[i - 1].first));
	printf("%lld\n", optimalDP);
}