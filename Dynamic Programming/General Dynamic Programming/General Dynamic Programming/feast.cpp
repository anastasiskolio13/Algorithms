#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#define MAXT 5000000
using namespace std;

int dp[MAXT + 1][2];
int T;
int A;
int B;

int main() {
	freopen("feast.in", "r", stdin);
	freopen("feast.out", "w", stdout);
	scanf("%d %d %d", &T, &A, &B);
	if (A > B)
		swap(A, B);
	for (int t = T; t >= T - A + 1; --t)
		dp[t][1] = t;
	for (int t = T - A; t >= T - B + 1; --t)
		dp[t][1] = dp[t + A][1];
	for (int t = T - B; t >= 0; --t)
		dp[t][1] = max(dp[t + A][1], dp[t + B][1]);
	for (int t = T; t >= T - A + 1; --t)
		dp[t][0] = max(t, dp[t / 2][1]);
	for (int t = T - A; t >= T - B + 1; --t)
		dp[t][0] = max(dp[t + A][0], dp[t / 2][1]);
	for (int t = T - B; t >= 0; --t)
		dp[t][0] = max({dp[t + A][0], dp[t + B][0], dp[t / 2][1]});
	printf("%d\n", dp[0][0]);
}