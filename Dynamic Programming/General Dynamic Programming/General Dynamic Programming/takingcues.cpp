#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 10000
#define INF 2e9
using namespace std;

vector<int> X(MAXN);
vector<int> Y(MAXN);
vector<int> B(MAXN);
vector<int> S(MAXN);
vector<vector<vector<int>>> dp(2, vector<vector<int>>(101, vector<int>(2)));
int N;
int M;

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; ++i)
		scanf("%d %d %d %d", &X[i], &Y[i], &B[i], &S[i]);
	dp[N % 2][0][0] = 0;
	for (int i = N - 1; i >= 0; --i) {
		for (int j = 0; j <= 100; ++j) {
			dp[i % 2][j][1] = dp[i % 2][j][0] = -INF;
			for (int k = 0; k <= min(100 - j, X[i]); ++k) 
				dp[i % 2][j][1] = max(dp[i % 2][j][1], dp[(i + 1) % 2][j + k][0] - k * B[i]);
			for (int k = 0; k <= min(j, Y[i]); ++k)
				dp[i % 2][j][0] = max(dp[i % 2][j][0], dp[i % 2][j - k][1] + k * S[i] - j * M);
		}
	}
	printf("%d\n", dp[0][0][0]);
}