#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 1000000
using namespace std;

vector<int> A(MAXN + 1);
vector<int> B(MAXN + 1);
vector<int> C(MAXN);
vector<vector<vector<int>>> dp(2, vector<vector<int>>(2, vector<int>(2)));
int N;

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i)
		scanf("%d", &A[i]);
	for (int i = 1; i <= N; ++i)
		scanf("%d", &B[i]);
	for (int i = 2; i <= N - 1; ++i)
		scanf("%d", &C[i]);
	dp[0][0][(N + 1) % 2] = dp[1][0][(N + 1) % 2] = 0;
	dp[0][1][(N + 1) % 2] = A[N];
	dp[1][1][(N + 1) % 2] = B[N];
	for (int j = N; j >= 2; --j) {
		dp[0][0][j % 2] = dp[1][0][j % 2] = max(dp[0][0][(j + 1) % 2], dp[0][1][(j + 1) % 2]);
		dp[0][1][j % 2] = max(dp[1][0][(j + 1) % 2] + A[j - 1], dp[1][1][(j + 1) % 2] + B[j - 1]);
		dp[1][1][j % 2] = max(dp[1][0][(j + 1) % 2] + B[j - 1], dp[1][1][(j + 1) % 2] + C[j - 1]);
	}
	printf("%d\n", max(dp[0][0][2 % 2], dp[0][1][2 % 2]));
}