#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cmath>
#define MAXN 5000
#define INF 1e14
using namespace std;

vector<int> V(MAXN + 1);
vector<int> P(MAXN + 1);
vector<vector<long long>> dp(2, vector<long long>(5001));
int N;

int C(int v) {
	return v % 2 == 0 ? floor((double)v / 2) + 1 : ceil((double)v / 2);
}

int main() {
	scanf("%d", &N);
	int sumOfPoints = 0;
	for (int i = 1; i <= N; ++i) {
		scanf("%d %d", &V[i], &P[i]);
		sumOfPoints += P[i];
	}
	for (int p = 0; p <= floor((double)sumOfPoints / 2); ++p)
		dp[0][p] = INF;
	for (int p = floor((double)sumOfPoints / 2) + 1; p <= sumOfPoints; ++p)
		dp[0][p] = 0;
	for (int i = 1; i <= N; ++i)
		for (int p = 0; p <= sumOfPoints; ++p)
			dp[i % 2][p] = min(dp[(i - 1) % 2][p], dp[(i - 1) % 2][p + P[i]] + C(V[i]));
	printf("%lld\n", dp[N % 2][0]);
}