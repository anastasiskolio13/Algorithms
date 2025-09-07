#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXA 2000
#define MAXM 2000
#define INF 2e9
using namespace std;

vector<bool> isRainyPoint(MAXA + 1);
vector<int> umbrellaPosition(MAXA + 1, -1);
vector<int> X(MAXM + 1);
vector<int> P(MAXM + 1);
vector<vector<int>> dp(2, vector<int>(MAXM + 1));
int A;
int N;
int M;

int main() {
	scanf("%d %d %d", &A, &N, &M);
	for (int i = 0; i < N; ++i) {
		int L, R;
		scanf("%d %d", &L, &R);
		for (int j = L; j < R; ++j)
			isRainyPoint[j] = true;
	}
	for (int i = 1; i <= M; ++i) {
		scanf("%d %d", &X[i], &P[i]);
		if (umbrellaPosition[X[i]] == -1)
			umbrellaPosition[X[i]] = i;
		else
			umbrellaPosition[X[i]] = P[umbrellaPosition[X[i]]] > P[i] ? i : umbrellaPosition[X[i]];
	}
	for (int i = A; i >= 0; --i) {
		for (int j = 0; j <= M; ++j) {
			if (!isRainyPoint[i]) {
				dp[i % 2][j] = umbrellaPosition[i] == -1 ? min(dp[(i + 1) % 2][j], dp[(i + 1) % 2][0]) + P[j] : min({ dp[(i + 1) % 2][j], dp[(i + 1) % 2][umbrellaPosition[i]], dp[(i + 1) % 2][0] }) + P[j];
			}
			else {
				if (umbrellaPosition[i] == -1 && j == 0)
					dp[i % 2][j] = INF;
				else if (umbrellaPosition[i] == -1 && j != 0)
					dp[i % 2][j] = dp[(i + 1) % 2][j] + P[j];
				else if (umbrellaPosition[i] != -1 && j == 0)
					dp[i % 2][j] = dp[(i + 1) % 2][umbrellaPosition[i]] + P[j];
				else
					dp[i % 2][j] = min(dp[(i + 1) % 2][j], dp[(i + 1) % 2][umbrellaPosition[i]]) + P[j];
			} 
		}
	}
	printf("%d\n", dp[0][0] == INF ? -1 : dp[0][0]);
}