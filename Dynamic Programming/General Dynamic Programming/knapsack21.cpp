#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#define MAXN 100
#define MAXVALSUM 100000
#define INF 1e18
using namespace std;

vector<int> W(MAXN + 1);
vector<int> V(MAXN + 1);
vector<vector<long long>> dp(2, vector<long long>(MAXVALSUM + 1));
int N;
int X;

int main() {
	scanf("%d %d", &N, &X);
	for (int i = 1; i <= N; ++i)
		scanf("%d %d", &W[i], &V[i]);
	int sumOfValues = accumulate(V.begin() + 1, V.begin() + N + 1, 0);
	int maximumValue = *max_element(V.begin() + 1, V.begin() + N + 1);
	dp[0][0] = 0;
	for (int v = 1; v <= sumOfValues; ++v)
		dp[0][v] = INF;
	for (int i = 1; i <= N; ++i) {
		for (int v = 0; v <= sumOfValues; ++v) {
			dp[i % 2][v] = dp[(i - 1) % 2][v];
			if (v >= V[i])
				dp[i % 2][v] = min(dp[i % 2][v], dp[(i - 1) % 2][v - V[i]] + W[i]);
		}
	}
	for (int v = sumOfValues; v >= maximumValue; --v) {
		if (dp[N % 2][v] <= X) {
			printf("%d\n", v);
			return 0;
		}
	}
}