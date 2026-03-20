#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#define MAXN 35000
#define INF 2e9
using namespace std;

vector<int> A(MAXN + 1);
vector<vector<int>> dp(2, vector<int>(MAXN + 1));
int N;
int K;

int C(set<int>& S) {
	return S.size();
}

void ComputeDP(int j, int lo, int hi, int opt_lo, int opt_hi) {
	if (lo > hi)
		return;
	set<int> S;
	int mid = (lo + hi) / 2;
	dp[j % 2][mid] = -INF;
	int opt_i;
	for (int i = min(opt_hi, mid); i >= opt_lo; --i) {
		S.insert(A[i]);
		if (dp[(j - 1) % 2][i - 1] + C(S) > dp[j % 2][mid]) {
			dp[j % 2][mid] = dp[(j - 1) % 2][i - 1] + C(S);
			opt_i = i;
		}
	}
	ComputeDP(j, lo, mid - 1, opt_lo, opt_i);
	ComputeDP(j, mid + 1, hi, opt_i, opt_hi);
}

int main() {
	scanf("%d %d", &N, &K);
	for (int i = 1; i <= N; ++i)
		scanf("%d", &A[i]);
	set<int> S;
	for (int i = 1; i <= N; ++i) {
		S.insert(A[i]);
		dp[1][i] = C(S);
	}
	for (int j = 2; j <= K; ++j)
		dp[j % 2][1] = -INF;
	for (int j = 2; j <= K; ++j)
		ComputeDP(j, 2, N, 2, N);
	printf("%d\n", dp[K % 2][N]);
}