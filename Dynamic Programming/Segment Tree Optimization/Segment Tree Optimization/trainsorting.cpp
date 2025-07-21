#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#define MAXN 2000
using namespace std;

set<pair<int, int>> S;
vector<vector<int>> verticalTrees(4 * MAXN, vector<int>(MAXN));
vector<vector<int>> horizontalTrees(MAXN, vector<int>(4 * MAXN));
vector<vector<int>> dp(MAXN, vector<int>(MAXN));
vector<int> A(MAXN);
vector<int> P(MAXN);
int N;

void Update(int lo, int hi, int v, int i, int x, int k, bool isHorizontalTree) {
	if (lo == hi) {
		isHorizontalTree ? horizontalTrees[k][v] = x : verticalTrees[v][k] = x;
		return;
	}
	int mid = (lo + hi) / 2;
	if (i <= mid)
		Update(lo, mid, 2 * v + 1, i, x, k, isHorizontalTree);
	else
		Update(mid + 1, hi, 2 * v + 1, i, x, k, isHorizontalTree);
	isHorizontalTree ? horizontalTrees[k][v] = max(horizontalTrees[k][2 * v + 1], horizontalTrees[k][2 * v + 2]) : verticalTrees[v][k] = max(verticalTrees[2 * v + 1][k], verticalTrees[2 * v + 2][k]);
}

int Query(int lo, int hi, int v, int qlo, int qhi, int k, bool isHorizontalTree) {
	if (qlo <= lo && hi <= qhi)
		return isHorizontalTree ? horizontalTrees[k][v] : verticalTrees[v][k];
	if (qlo > hi || qhi < lo)
		return 0;
	int mid = (lo + hi) / 2;
	int maxLeft = Query(lo, mid, 2 * v + 1, qlo, qhi, k, isHorizontalTree);
	int maxRight = Query(mid + 1, hi, 2 * v + 2, qlo, qhi, k, isHorizontalTree);
	return max(maxLeft, maxRight);
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		scanf("%d", &A[i]);
		S.insert({ A[i], i });
	}
	int i = 0;
	for (auto [_, index] : S)
		P[index] = i++;
	for (int i = N - 1; i >= 0; --i) {
		for (int j = N - 1; j >= 0; --j) {
			dp[i][j] = 1;
			auto iteratorOne = S.upper_bound({ A[i], N });
			auto iteratorTwo = S.lower_bound({ A[j], -1 });
			if (iteratorOne != S.end())
				dp[i][j] = max(dp[i][j], Query(0, N - 1, 0, P[iteratorOne->second], N - 1, false) + 1);

		}
	}
	int ans = 0;
	for (int i = 0; i < N; ++i)
		ans = max(ans, dp[i][i]);
	printf("%d\n", ans);
}