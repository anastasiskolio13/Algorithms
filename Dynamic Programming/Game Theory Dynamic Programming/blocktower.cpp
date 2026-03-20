#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 20
using namespace std;

vector<int> H(MAXN);
vector<bool> dp(1 << MAXN);
int N;
int K;

int main() {
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; ++i)
		scanf("%d", &H[i]);
	for (int s = 1; s < (1 << N); ++s) {
		long long sumOfComplement = 0;
		for (int i = 0; i < N; ++i)
			if (!(s & (1 << i)))
				sumOfComplement += H[i];
		dp[s] = false;
		for (int i = 0; i < N; ++i)
			if (s & (1 << i) && sumOfComplement + H[i] <= K)
				dp[s] = dp[s] || !dp[s & ~(1 << i)];
	}
	printf(dp[(1 << N) - 1] ? "win" : "lose");
}