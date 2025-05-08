#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 100000
using namespace std;

vector<int> A(MAXN);
vector<int> B(MAXN);
vector<int> C(MAXN);
vector<vector<int>> dp(2, vector<int>(3));
int N;

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
		scanf("%d %d %d", &A[i], &B[i], &C[i]);
	dp[N % 2][0] = dp[N % 2][1] = dp[N % 2][2] = 0;
	for (int i = N - 1; i >= 1; --i) {
		dp[i % 2][0] = max(dp[(i + 1) % 2][1] + B[i], dp[(i + 1) % 2][2] + C[i]);
		dp[i % 2][1] = max(dp[(i + 1) % 2][0] + A[i], dp[(i + 1) % 2][2] + C[i]);
		dp[i % 2][2] = max(dp[(i + 1) % 2][0] + A[i], dp[(i + 1) % 2][1] + B[i]);
	}
	printf("%d\n", max({dp[1][0] + A[0], dp[1][1] + B[0], dp[1][2] + C[0]}));
}