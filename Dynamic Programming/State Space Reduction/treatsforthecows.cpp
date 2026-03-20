#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 2000
using namespace std;

vector<int> A(MAXN + 1);
vector<vector<int>> dp(MAXN + 1, vector<int>(MAXN + 1));
int N;

int C(int i, int j, bool isFromTheLeft) {
	if (isFromTheLeft)
		return A[i] * (N - j + i);
	return A[j] * (N - j + i);
}

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i)
		scanf("%d", &A[i]);
	for (int i = 1; i <= N; ++i)
		dp[i][i] = A[i] * N;
	for (int l = 2; l <= N; ++l)
		for (int i = 1; i <= N - l + 1; ++i)
			dp[i][i + l - 1] = max(dp[i + 1][i + l - 1] + C(i, i + l - 1, true), dp[i][i + l - 2] + C(i, i + l - 1, false));
	printf("%d\n", dp[1][N]);
}