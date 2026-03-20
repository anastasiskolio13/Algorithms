#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 500
#define MAXM 500
#define A 0
#define B 1
using namespace std;

vector<vector<int>> C(MAXN + 1, vector<int>(MAXM + 1));
vector<vector<vector<long long>>> dp(MAXN + 1, vector<vector<long long>>(MAXM + 1, vector<long long>(2)));
int N;
int M;
int K;

int main() {
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= M; ++j)
			scanf("%d", &C[i][j]); 
	for (int i1 = N; i1 >= 1; --i1) {
		for (int j1 = M; j1 >= 1; --j1) {
			for (int i2 = i1; i2 <= min(i1 + K, N); ++i2) {
				for (int j2 = j1; j2 <= min(j1 + K, M); ++j2) {
					if (i1 == i2 && j1 == j2)
						continue;
					dp[i1][j1][A] = max(dp[i1][j1][A], dp[i2][j2][B] + C[i2][j2]);
					dp[i1][j1][B] = min(dp[i1][j1][B], dp[i2][j2][A]);
				}
			}
		}
	}
	printf("%lld\n", dp[1][1][A]);
}