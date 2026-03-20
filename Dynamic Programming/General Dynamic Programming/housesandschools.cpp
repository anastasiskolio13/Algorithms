#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 3000
#define INF 1e18
using namespace std;

vector<int> A(MAXN + 1);
vector<pair<long long, long long>> PS(MAXN + 1);
vector<vector<long long>> dp(2, vector<long long>(MAXN + 1));
int N;
int K;

long long C(int i, int j) {
	int mid = (i + j) / 2;
	return PS[mid].second - PS[i - 1].second - i * (PS[mid].first - PS[i - 1].first) + j * (PS[j].first - PS[mid].first) - PS[j].second + PS[mid].second;
}

int main() {
	scanf("%d %d", &N, &K);
	for (int i = 1; i <= N; ++i) {
		scanf("%d", &A[i]);
		PS[i].first = PS[i - 1].first + A[i];
		PS[i].second = PS[i - 1].second + (long long)A[i] * i;
	}
	for (int i = 1; i <= N; ++i)
		dp[0][i] = i * PS[i].first - PS[i].second;
	for (int j = 1; j < K; ++j) {
		dp[j % 2][1] = INF;
		for (int i = 2; i <= N; ++i) {
			dp[j % 2][i] = INF;
			for (int k = 1; k <= i - 1; ++k)
				dp[j % 2][i] = min(dp[j % 2][i], dp[(j - 1) % 2][k] + C(k, i));
		}
	}
	long long optimalDP = INF;
	for (int i = 1; i <= N; ++i)
		optimalDP = min(optimalDP, dp[(K - 1) % 2][i] + PS[N].second - PS[i - 1].second - i * (PS[N].first - PS[i - 1].first));
	printf("%lld\n", optimalDP);
}