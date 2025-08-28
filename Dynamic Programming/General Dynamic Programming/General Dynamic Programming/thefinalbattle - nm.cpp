#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 100
#define MAXM 100
#define INF 2e9
using namespace std;

vector<vector<int>> C(MAXN + 1, vector<int>(MAXM + 1));
vector<vector<int>> dp(2, vector<int>(MAXN + 1));
vector<int> previousPrefixMin(MAXN + 1);
vector<int> previousSuffixMin(MAXN + 2);
int T;
int N;
int M;

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &N, &M);
		for (int i = 1; i <= N; ++i)
			for (int j = 1; j <= M; ++j)
				scanf("%d", &C[i][j]);
		for (int j = 1; j <= N; ++j) 
			dp[(M + 1) % 2][j] = 0;
		previousPrefixMin[0] = INF;
		for (int j = 1; j <= N; ++j)
			previousPrefixMin[j] = min(previousPrefixMin[j - 1], dp[(M + 1) % 2][j] + C[j][M]);
		previousSuffixMin[N + 1] = INF;
		for (int j = N; j >= 1; --j)
			previousSuffixMin[j] = min(previousSuffixMin[j + 1], dp[(M + 1) % 2][j] + C[j][M]);
		for (int i = M; i >= 2; --i) {
			for (int j = 1; j <= N; ++j)
				dp[i % 2][j] = min(previousPrefixMin[j - 1], previousSuffixMin[j + 1]);
			previousPrefixMin[0] = INF;
			for (int j = 1; j <= N; ++j)
				previousPrefixMin[j] = min(previousPrefixMin[j - 1], dp[i % 2][j] + C[j][i - 1]);
			previousSuffixMin[N + 1] = INF;
			for (int j = N; j >= 1; --j)
				previousSuffixMin[j] = min(previousSuffixMin[j + 1], dp[i % 2][j] + C[j][i - 1]);
		}
		int minimumTime = INF;
		for (int i = 1; i <= N; ++i)
			minimumTime = min(minimumTime, dp[2 % 2][i] + C[i][1]);
		printf("%d\n", minimumTime);
	}
}