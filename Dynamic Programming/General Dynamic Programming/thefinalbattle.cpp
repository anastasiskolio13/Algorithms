#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 100
#define MAXM 100
#define INF 2e9
using namespace std;

vector<vector<int>> C(MAXN, vector<int>(MAXM));
vector<vector<int>> dp(2, vector<int>(MAXN));
int T;
int N;
int M;

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &N, &M);
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < M; ++j)
				scanf("%d", &C[i][j]);
		for (int i = 0; i < N; ++i)
			dp[M % 2][i] = 0;
		for (int i = M - 1; i >= 1; --i) {
			for (int j = 0; j < N; ++j) {
				dp[i % 2][j] = INF;
				for (int k = 0; k < N; ++k)
					if (k != j)
						dp[i % 2][j] = min(dp[i % 2][j], dp[(i + 1) % 2][k] + C[k][i]);
			}
		}
		int minimumTime = INF;
		for (int i = 0; i < N; ++i)
			minimumTime = min(minimumTime, dp[1][i] + C[i][0]);
		printf("%d\n", minimumTime);
	}
}