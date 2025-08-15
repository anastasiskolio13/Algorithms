#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 19
#define INF 2e9
using namespace std;

vector<int> A(MAXN);
vector<int> M(MAXN);
vector<int> dp(1 << MAXN);
int N;


int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
		scanf("%d", &A[i]);
	for (int i = 0; i < N; ++i)
		scanf("%d", &M[i]);
	dp[0] = 0;
	for (int s = 1; s < (1 << N); ++s) {
		int subsetSize = popcount(static_cast<unsigned int>(s));
		dp[s] = -INF;
		for (int i = 0; i < N; ++i)
			if (s & (1 << i))
				dp[s] = max(dp[s], dp[s & ~(1 << i)] + A[i] * M[/* index of the element at the ith position at the start of round N - subsetSize + 1 */]);
	}
	printf("%d\n", dp[(1 << N) - 1]);
}