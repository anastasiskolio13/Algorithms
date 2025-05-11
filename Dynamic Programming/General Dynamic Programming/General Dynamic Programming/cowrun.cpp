#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 1000
using namespace std;

vector<int> X(MAXN + 1);
vector<int> L(MAXN + 1);
vector<int> R(MAXN + 1);
vector<vector<vector<long long>>> dp(MAXN + 2, vector<vector<long long>>(MAXN + 2, vector<long long>(2)));
int N;
int N1;
int N2;

int main() {
	freopen("cowrun.in", "r", stdin);
	freopen("cowrun.out", "w", stdout);

	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) {
		scanf("%d", &X[i]);
		X[i] < 0 ? L[++N1] = X[i] : R[++N2] = X[i];
	}
	
	sort(L.begin() + 1, L.begin() + N1 + 1);
	sort(R.begin() + 1, R.begin() + N2 + 1);

	for (int i = 0; i <= N1; ++i) {
		for (int j = N2 + 1; j >= 1; --j) {
			if (i == 0 && j == N2 + 1) {
				dp[i][j][0] = 0;
				dp[i][j][1] = 0;
			}
			else if (i == 0 && 1 <= j && j <= N2) {
				dp[i][j][0] = dp[0][j + 1][1] + (N2 - j + 1) * (R[j] - L[1]);
				dp[i][j][1] = dp[0][j + 1][1] + (N2 - j + 1) * (R[j] - R[j - 1]);
			}
			else if (1 <= i && i <= N1 && j == N2 + 1) {
				dp[i][j][0] = dp[i - 1][N2 + 1][0] + i * (L[i + 1] - L[i]);
				dp[i][j][1] = dp[i - 1][N2 + 1][0] + i * (R[N2] - L[i]);
			}
			else {
				dp[i][j][0] = min(dp[i - 1][j][0] + (i + N2 - j + 1) * (L[i + 1] - L[i]), dp[i][j + 1][1] + (i + N2 - j + 1) * (R[j] - L[i + 1]));
				dp[i][j][1] = min(dp[i - 1][j][0] + (i + N2 - j + 1) * (R[j - 1] - L[i]), dp[i][j + 1][1] + (i + N2 - j + 1) * (R[j] - R[j - 1]));
			}
		}
	}
	if (N1 == 0)
		printf("%lld\n", dp[0][2][1] + N * R[1]);
	else if (N2 == 0)
		printf("%lld\n", dp[N1 - 1][1][0] - N * L[N1]);
	else 
		printf("%lld\n", min(dp[N1 - 1][1][0] - N * L[N1], dp[N1][2][1] + N * R[1]));
}
