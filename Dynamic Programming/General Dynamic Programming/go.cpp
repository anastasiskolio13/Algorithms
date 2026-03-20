#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 1000
#define MAXM 100
#define MAXT 2000
using namespace std;

vector<int> L(MAXM + 1);
vector<int> R(MAXM + 1);
vector<pair<int, int>> X(MAXN + 1);
int dp[2][MAXM + 1][MAXT + 2][2];	
int N;
int K;
int M;
int N1;
int N2;

int C(int t, int idx) {
	return X[idx].first * (t < X[idx].second);
}

int main() {
	scanf("%d %d %d", &N, &K, &M);
	for (int i = 1; i <= M; ++i) {
		int a, b, t;
		scanf("%d %d %d", &a, &b, &t);
		X[a] = { b, t };
		a <= K ? L[++N1] = a : R[++N2] = a;
	}
	for (int i = 0; i <= N1; ++i) {
		for (int j = N2 + 1; j >= 1; --j) {
			for (int t = 0; t <= MAXT + 1; ++t) {
				if (i == 0 && j == N2 + 1) {
					dp[i % 2][j][t][0] = 0;
					dp[i % 2][j][t][1] = 0;
				}
				else if (i == 0 && 1 <= j && j <= N2) {
					dp[i % 2][j][t][0] = dp[0][j + 1][min(t + R[j] - L[1], MAXT + 1)][1] + C(min(t + R[j] - L[1], MAXT + 1), R[j]);
					dp[i % 2][j][t][1] = dp[0][j + 1][min(t + R[j] - R[j - 1], MAXT + 1)][1] + C(min(t + R[j] - R[j - 1], MAXT + 1), R[j]);
				}
				else if (1 <= i && i <= N1 && j == N2 + 1) {
					dp[i % 2][j][t][0] = dp[(i - 1) % 2][N2 + 1][min(t + L[i + 1] - L[i], MAXT + 1)][0] + C(min(t + L[i + 1] - L[i], MAXT + 1), L[i]);
					dp[i % 2][j][t][1] = dp[(i - 1) % 2][N2 + 1][min(t + R[N2] - L[i], MAXT + 1)][0] + C(min(t + R[N2] - L[i], MAXT + 1), L[i]);
				}
				else {
					dp[i % 2][j][t][0] = max(dp[(i - 1) % 2][j][min(t + L[i + 1] - L[i], MAXT + 1)][0] + C(min(t + L[i + 1] - L[i], MAXT + 1), L[i]), dp[i % 2][j + 1][min(t + R[j] - L[i + 1], MAXT + 1)][1] + C(min(t + R[j] - L[i + 1], MAXT + 1), R[j]));
					dp[i % 2][j][t][1] = max(dp[(i - 1) % 2][j][min(t + R[j - 1] - L[i], MAXT + 1)][0] + C(min(t + R[j - 1] - L[i], MAXT + 1), L[i]), dp[i % 2][j + 1][min(t + R[j] - R[j - 1], MAXT + 1)][1] + C(min(t + R[j] - R[j - 1], MAXT + 1), R[j]));
				}
			}
		}
	}
	if (N1 == 0)
		printf("%d\n", dp[0][2][R[1] - K][1] + C(R[1] - K, R[1]));
	else if (N2 == 0)
		printf("%d\n", dp[(N1 - 1) % 2][1][K - L[N1]][0] + C(K - L[N1], L[N1]));
	else
		printf("%d\n", max(dp[(N1 - 1) % 2][1][K - L[N1]][0] + C(K - L[N1], L[N1]), dp[N1 % 2][2][R[1] - K][1] + C(R[1] - K, R[1])));
}