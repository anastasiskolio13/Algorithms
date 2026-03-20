#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 100000
#define MAXM 10
using namespace std;

vector<int> X(MAXM);
vector<bool> dp(MAXN + 1);
int M;
int Q;

int main() {
	scanf("%d", &M);
	for (int i = 0; i < M; ++i)
		scanf("%d", &X[i]);
	dp[0] = false;
	for (int i = 1; i <= MAXN; ++i) {
		dp[i] = false;
		for (int j = 0; j < M; ++j)
			if (X[j] <= i)
				dp[i] = dp[i] || !dp[i - X[j]];
	}
	scanf("%d", &Q);
	while (Q--) {
		int N;
		scanf("%d", &N);
		printf("%d\n", (int)dp[N]);
	}
}