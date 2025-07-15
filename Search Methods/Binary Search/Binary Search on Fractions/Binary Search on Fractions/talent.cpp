#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <cfloat>
#include <cmath>
#define MAXN 250
#define MAXW 1000
#define eps 1e-6
#define INF DBL_MAX
using namespace std;

vector<int> W(MAXN + 1);
vector<int> T(MAXN + 1);
vector<vector<double>> dp(MAXN + 1, vector<double>(MAXW + 1));
int N;
int X;

double ComputeDP(double k) {
	dp[0][0] = 0;
	for (int x = 1; x <= X; ++x)
		dp[0][x] = INF;
	for (int i = 1; i <= N; ++i)
		for (int x = 0; x <= X; ++x)
			dp[i][x] = min(dp[i - 1][x], dp[i - 1][max(x - W[i], 0)] + k * W[i] - T[i]);
	return dp[N][X];
}

int main() {
	freopen("talent.in", "r", stdin);
	freopen("talent.out", "w", stdout);
	scanf("%d %d", &N, &X);
	for (int i = 1; i <= N; ++i)
		scanf("%d %d", &W[i], &T[i]);
	double lo = 0;
	double hi = *max_element(T.begin() + 1, T.begin() + N + 1);
	while (hi - lo > eps) {
		double mid = (lo + hi) / 2;
		if (ComputeDP(mid) <= 0)
			lo = mid;
		else
			hi = mid;
	}
	printf("%lld\n", (long long)floor(lo * 1000));
}