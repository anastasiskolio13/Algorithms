#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 20000
#define INF 2e9
using namespace std;

vector<int> W(MAXN + 1);
vector<int> D(MAXN + 1);
vector<int> PSW(MAXN + 1);
vector<int> PSD(MAXN + 1);
vector<int> PSC(MAXN + 1);
vector<vector<int>> dp(2, vector<int>(MAXN + 2));
int N;

int C(int i, int j) {
	return PSD[j - 1] * (PSW[j - 1] - PSW[i - 1]) - PSC[j - 1] + PSC[i - 1];
}

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) {
		scanf("%d %d", &W[i], &D[i]);
		PSW[i] = PSW[i - 1] + W[i];
		PSD[i] = PSD[i - 1] + D[i];
		PSC[i] = PSC[i - 1] + W[i] * PSD[i - 1];
	}
	dp[0][0] = 0;
	for (int i = 1; i <= N + 1; ++i)
		dp[0][i] = INF;
	for (int j = 1; j <= 3; ++j) {
		for (int i = 1; i <= N + 1; ++i) {
			dp[j % 2][i] = INF;
			for (int k = 1; k <= i; ++k)
				dp[j % 2][i] = min(dp[j % 2][i], dp[(j - 1) % 2][k - 1] + C(k, i));
		}
	}
	printf("%d\n", dp[1][N + 1]);
}