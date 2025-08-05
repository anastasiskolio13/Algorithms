#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 100000
#define MAXM 6
#define INF 1e18
using namespace std;

vector<int> A(MAXN);
vector<int> S(MAXM);
vector<vector<long long>> dp(1 << MAXM, vector<long long>(MAXN + 1));
int N;
int M;
int P;
int C;

int main() {
	scanf("%d %d %d %d", &N, &M, &P, &C);
	for (int i = 0; i < N; ++i)
		scanf("%d", &A[i]);
	for (int i = 0; i < M; ++i)
		scanf("%d", &S[i]);
	sort(A.begin(), A.begin() + N);
	dp[0][N] = 0;
	for (int s = 1; s < 1 << M; ++s)
		dp[s][N] = -INF;
	for (int j = N - 1; j >= 0; --j) {
		for (int s = 0; s < 1 << M; ++s) {
			dp[s][j] = dp[s][j + 1];
			for (int i = 0; i < M; ++i)
				if (s & (1 << i) && j + S[i] - 1 < N)
					dp[s][j] = max(dp[s][j], max(dp[s & ~(1 << i)][j + S[i]], dp[s][j + S[i]]) + P - (long long)(A[j + S[i] - 1] - A[j]) * (A[j + S[i] - 1] - A[j]) * C);
		}
	}
	printf("%lld\n", dp[(1 << M) - 1][0]);
}