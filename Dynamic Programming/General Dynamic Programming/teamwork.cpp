#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define INF 1e18
#define MAXN 10000
using namespace std;

vector<int> S(MAXN + 1);
vector<long long> dp(MAXN + 2);	
int N;
int K;

int main() {
	freopen("teamwork.in", "r", stdin);
	freopen("teamwork.out", "w", stdout);
	scanf("%d %d", &N, &K);
	for (int i = 1; i <= N; ++i)
		scanf("%d", &S[i]);
	dp[N + 1] = 0;
	for (int i = N; i >= 1; --i) {
		int maxElement = 0;
		dp[i] = -INF;
		for (int j = i; j <= min(i + K - 1, N); ++j) {
			maxElement = max(maxElement, S[j]);
			dp[i] = max(dp[i], dp[j + 1] + (j - i + 1) * maxElement);
		}
	}
	printf("%lld\n", dp[1]);
}