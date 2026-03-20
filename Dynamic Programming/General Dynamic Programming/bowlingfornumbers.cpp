#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 30000
#define INF 2e9
using namespace std;

int T;
int N;
int K;
int W;

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d %d", &N, &K, &W);
		vector<int> B(N + 1);
		vector<int> PS(MAXN + 1);
		vector<vector<int>> dp(2, vector<int>(N + 1, -INF));
		PS[0] = 0;
		for (int i = 1; i <= N; ++i) {
			scanf("%d", &B[i]);
			PS[i] = PS[i - 1] + B[i];
		}
		for (int j = 0; j <= K; ++j)
			dp[j % 2][0] = 0;
		for (int i = 1; i <= N; ++i)
			dp[0][i] = 0;
		for (int j = 1; j <= K; ++j)
			for (int i = 1; i <= N; ++i)
				dp[j % 2][i] = max(dp[j % 2][i - 1], dp[(j - 1) % 2][max(i - W, 0)] + PS[i] - PS[max(i - W, 0)]);
		printf("%d\n", dp[K % 2][N]);
	}
}