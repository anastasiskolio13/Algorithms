#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#define MAXN 1000
#define MAXM 1000
#define MOD 1000000007
using namespace std;

priority_queue<tuple<int, int, int>> Q;
vector<vector<int>> A(MAXN, vector<int>(MAXM));
vector<vector<int>> dp(MAXN, vector<int>(MAXM));
int N;
int M;

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			scanf("%d", &A[i][j]);
			Q.push({ A[i][j], i, j });
		}
	}
	while (!Q.empty()) {
		int i = get<1>(Q.top());
		int j = get<2>(Q.top());
		Q.pop();
		if (i == N - 1 && j == M - 1) {
			dp[N - 1][M - 1] = 1;
			continue;
		}
		if (i - 1 >= 0 && A[i][j] < A[i - 1][j])
			dp[i][j] = (dp[i][j] + dp[i - 1][j]) % MOD;
		if (i + 1 < N && A[i][j] < A[i + 1][j])
			dp[i][j] = (dp[i][j] + dp[i + 1][j]) % MOD;
		if (j - 1 >= 0 && A[i][j] < A[i][j - 1])
			dp[i][j] = (dp[i][j] + dp[i][j - 1]) % MOD;
		if (j + 1 < M && A[i][j] < A[i][j + 1])
			dp[i][j] = (dp[i][j] + dp[i][j + 1]) % MOD;
	}
	printf("%d\n", dp[0][0]);
}