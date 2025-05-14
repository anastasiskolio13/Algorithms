#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 1000000
using namespace std;

vector<bool> dp(MAXN + 1);
int K;
int L;
int M;

int main() {
	freopen("coinstack.in", "r", stdin);
	freopen("coinstack.out", "w", stdout);
	scanf("%d %d %d", &K, &L, &M);
	dp[0] = false;
	for (int i = 1; i <= MAXN; ++i) {
		dp[i] = !dp[i - 1];
		if (i >= K)
			dp[i] = dp[i] || !dp[i - K];
		if (i >= L)
			dp[i] = dp[i] || !dp[i - L];
	}
	while (M--) {
		int Ni;
		scanf("%d", &Ni);
		printf(dp[Ni] ? "A" : "B");
	}
}