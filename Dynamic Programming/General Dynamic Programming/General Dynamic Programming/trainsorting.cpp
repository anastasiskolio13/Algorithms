#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 2000
using namespace std;

vector<vector<int>> dp(MAXN, vector<int>(MAXN));
vector<int> A(MAXN);
int N;

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
		scanf("%d", &A[i]);
	for (int i = N - 1; i >= 0; --i) {
		for (int j = N - 1; j >= 0; --j) {
			dp[i][j] = 1;
			for (int k = max(i, j) + 1; k < N; ++k) {
				if (A[k] > A[i])
					dp[i][j] = max(dp[i][j], dp[k][j] + 1);
				if (A[k] < A[j])
					dp[i][j] = max(dp[i][j], dp[i][k] + 1);
			}
		}
	}
	int ans = 0;
	for (int i = 0; i < N; ++i)
		ans = max(ans, dp[i][i]);
	printf("%d\n", ans);
}