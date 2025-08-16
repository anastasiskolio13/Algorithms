#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 500
#define MAXM 500
#define MAXK 500
using namespace std;

vector<int> P(MAXN + 1);
vector<int> B(MAXM + 1);
vector<vector<int>> dp(2, vector<int>(MAXK + 1));
int N;
int M;
int K;

int main() {
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 1; i <= N; ++i)
		scanf("%d", &P[i]);
	for (int i = 0; i <= M; ++i)
		scanf("%d", &B[i]);
	for (int i = 1; i <= N; ++i)
		for (int j = 0; j <= K; ++j)
			for (int k = 0; k <= min(M - P[i], j); ++k)
				dp[i % 2][j] = max(dp[i % 2][j], dp[(i - 1) % 2][j - k] + B[P[i] + k]);
	printf("%d\n", dp[N % 2][K]);
}