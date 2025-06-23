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
	return X[j] * (PSW[j - 1] - PSW[i - 1]) - (PSXW[j - 1] - PSXW[i - 1]);
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
	for (int i = 1; i <= N; ++i)
		dp[1][i] = C(1, i);
	for (int j = 2; j <= K; ++j) {
		for (int i = 2; i <= N; ++i) {
			dp[j % 2][i] = INF;
			for (int r = 2; r <= i; ++r)
				dp[j % 2][i] = min(dp[j % 2][i], dp[(j - 1) % 2][r - 1] + C(r, i));
		}
	}
	printf("%lld\n", dp[K % 2][N]);
}