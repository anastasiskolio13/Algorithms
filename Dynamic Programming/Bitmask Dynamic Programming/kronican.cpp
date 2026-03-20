#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 20
#define INF 2e9
using namespace std;

vector<vector<int>> C(MAXN, vector<int>(MAXN));
vector<int> dp(1 << MAXN);
int N;
int K;

int main() {
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			scanf("%d", &C[i][j]);
	for (int s = 0; s < (1 << N); ++s) {
		int subsetSize = popcount(static_cast<unsigned int>(s));
		if (subsetSize <= K)
			continue;
		dp[s] = INF;
		for (int i = 0; i < N; ++i)
			if (s & (1 << i))
				for (int j = 0; j < N; ++j)
					if (s & (1 << j) && j != i)
						dp[s] = min(dp[s], dp[s & ~(1 << i)] + C[i][j]);
	}
	printf("%d\n", dp[(1 << N) - 1]);
}