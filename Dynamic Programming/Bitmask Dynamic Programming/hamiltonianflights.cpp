#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 20
#define MOD 1000000007
using namespace std;

vector<vector<int>> Adj(MAXN);
vector<vector<int>> dp(1 << MAXN, vector<int>(MAXN));
int N;
int M;

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; ++i) {
		int v, u;
		scanf("%d %d", &v, &u);
		Adj[--v].push_back(--u);
	}
	dp[0][N - 1] = 1;
	for (int s = 1; s < (1 << N); ++s)
		dp[s][N - 1] = 0;
	for (int s = 1; s < (1 << N); ++s) {
		for (int i = 0; i < N - 1; ++i) {
			dp[s][i] = 0;
			if (s & (1 << i))
				continue;
			for (int j : Adj[i])
				if (s & (1 << j))
					dp[s][i] = (dp[s][i] + dp[s & ~(1 << j)][j]) % MOD;
		}
	}
	printf("%d\n", dp[(1 << N) - 1 & ~(1 << 0)][0]);
}