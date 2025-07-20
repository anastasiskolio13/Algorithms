#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 5000
#define MAXW 5000
using namespace std;

vector<int> G(MAXN + 1);
vector<int> H(MAXN + 1);
vector<int> Q(MAXN + 1);
vector<int> T(MAXN + 1);
vector<vector<vector<long long>>> dp(2, vector<vector<long long>>(MAXW + 1, vector<long long>(2)));
int N;
int W;

int main() {
	scanf("%d %d", &N, &W);
	for (int i = 1; i <= N; ++i)
		scanf("%d %d %d %d", &G[i], &H[i], &Q[i], &T[i]);
	for (int w = 0; w <= W; ++w)
		dp[0][w][0] = 0;
	for (int i = 1; i <= N; ++i) {
		for (int w = 0; w <= W; ++w) {
			dp[i % 2][w][0] = dp[i % 2][w][1] = dp[(i - 1) % 2][w][0];
			if (H[i] <= w)
				dp[i % 2][w][0] = max(dp[i % 2][w][0], dp[i % 2][w - H[i]][1] + G[i]);
			if (T[i] <= w)
				dp[i % 2][w][1] = max(dp[i % 2][w][1], dp[i % 2][w - T[i]][1] + Q[i]);
		}
	}
	printf("%lld\n", dp[N % 2][W][0]);
}