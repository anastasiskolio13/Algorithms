#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 100000
#define MAXM_max 500
#define INF 1000000000
using namespace std;

vector<int> A(MAXN + 1);
vector<vector<int>> dp(2, vector<int>(MAXM_max + 1));
int N;
int M_max;
int K;

bool isCouponPosition(int i) {
	return i % K == 0;
}

int main() {
	scanf("%d %d %d", &N, &M_max, &K);
	for (int i = 1; i <= N; ++i)
		scanf("%d", &A[i]);
	int optimalDP = 0;
	for (int M = 0; M <= M_max; ++M) {
		dp[(N + 1) % 2][M] = 0;
		for (int j = 0; j < M; ++j)
			dp[(N + 1) % 2][j] = -INF;
		for (int i = N; i >= 1; --i) {
			dp[i % 2][min(i - 1, M)] = dp[(i + 1) % 2][min(i - 1, M)] + A[i] * isCouponPosition(i - min(i - 1, M));
			for (int j = min(i - 1, M - 1); j >= 0; --j)
				dp[i % 2][j] = max(dp[(i + 1) % 2][j] + A[i] * isCouponPosition(i - j), dp[(i + 1) % 2][j + 1] + A[i] * isCouponPosition(N - M + j + 1));
		}
		optimalDP = max(optimalDP, dp[1][0]);
	}
	printf("%d\n", optimalDP);
}