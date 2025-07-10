#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <unordered_map>
#define MAXT 10
using namespace std;

unordered_map<int, long long> dp;
vector<int> X(MAXT);
int T;

long long OptimalExchange(int x) {
	if (dp.find(x) != dp.end())
		return dp[x];
	if (x == 0)
		return 0;
	return dp[x] = max(OptimalExchange(x / 2) + OptimalExchange(x / 3) + OptimalExchange(x / 4), (long long)x);
}

int main() {
	scanf("%d", &T);
	for (int i = 0; i < T; ++i) {
		scanf("%d", &X[i]);
		printf("%lld\n", OptimalExchange(X[i]));
	}
}