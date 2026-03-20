#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXT 10
#define MAXX 10000000
using namespace std;

int T;
vector<int> Q(MAXT);
vector<int> dp(MAXX + 1);

int main() {
	scanf("%d", &T);
	for (int i = 0; i < T; ++i)
		scanf("%d", &Q[i]);
	dp[0] = 0;
	for (int x = 1; x <= MAXX; ++x)
		dp[x] = max(dp[x / 2] + dp[x / 3] + dp[x / 4], x);
	for (int i = 0; i < T; ++i)
		printf("%d\n", dp[Q[i]]);
}