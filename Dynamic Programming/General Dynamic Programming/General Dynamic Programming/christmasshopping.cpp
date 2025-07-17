#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#define MAXN 100000
#define MAXR 10
#define MAXC 10
using namespace std;

int X[MAXN + 3];
int Y[MAXN + 3];
long long dp[2][MAXR + 1][MAXC + 1];
int N;
int R;
int C;

int main() {
	scanf("%d %d %d", &N, &R, &C);
	for (int i = 1; i <= N + 2; ++i)
		scanf("%d %d", &X[i], &Y[i]);
	for (int x = 1; x <= R; x++)
		for (int y = 1; y <= C; ++y)
			dp[(N + 3) % 2][x][y] = 0;
	for (int i = N + 2; i >= 3; --i)
		for (int x = 1; x <= R; x++)
			for (int y = 1; y <= C; ++y)
				dp[i % 2][x][y] = min(dp[(i + 1) % 2][x][y] + abs(X[i] - X[i - 1]) + abs(Y[i] - Y[i - 1]), dp[(i + 1) % 2][X[i - 1]][Y[i - 1]] + abs(X[i] - x) + abs(Y[i] - y));
	printf("%lld\n", dp[3 % 2][X[1]][Y[1]]);
}