#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 1000
#define MAXW 20000
using namespace std;

struct block {
	int W;
	int S;
	int V;
};

bool compareBlocks(block A, block B) {
	return A.S + A.W > B.S + B.W;
}

vector<block> B(MAXN + 1);
vector<vector<long long>> dp(2, vector<long long>(MAXW + 1));
int N;

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i)
		scanf("%d %d %d", &B[i].W, &B[i].S, &B[i].V);
	sort(B.begin() + 1, B.begin() + N + 1, compareBlocks);
	for (int i = 1; i <= N; ++i) {
		for (int w = 0; w <= MAXW; ++w) {
			dp[i % 2][w] = dp[(i - 1) % 2][w];
			if (B[i].S >= w)
				dp[i % 2][w] = max(dp[i % 2][w], dp[(i - 1) % 2][w + B[i].W] + B[i].V);
		}
	}
	printf("%lld\n", dp[N % 2][0]);
}