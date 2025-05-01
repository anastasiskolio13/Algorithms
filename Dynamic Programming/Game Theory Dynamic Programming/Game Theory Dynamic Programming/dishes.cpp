#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN1 1000
#define MAXN2 1000
using namespace std;

vector<vector<bool>> dp(MAXN1 + 1, vector<bool>(MAXN2 + 1));
int M;

int main() {
	for (int i = 0; i <= MAXN1; ++i) {
		for (int j = 0; j <= MAXN2; ++j) {
			if (i == 0 && j == 0) {
				dp[i][j] = false;
				continue;
			}
			if (i == 0 && j == 1 || i == 1 && j == 0 || i == 1 && j == 1) {
				dp[i][j] = true;
				continue;
			}
			if (i > 0)
				dp[i][j] = !dp[i - 1][j];
			if (j > 0)
				dp[i][j] = dp[i][j] || !dp[i][j - 1];
			if (i > 0 && j > 0)
				dp[i][j] = dp[i][j] || !dp[i - 1][j - 1];
		}
	}
	scanf("%d", &M);
	while (M--) {
		int N1, N2;
		scanf("%d %d", &N1, &N2);
		printf("%d\n", dp[N1][N2] ? 1 : 2);
	}
}