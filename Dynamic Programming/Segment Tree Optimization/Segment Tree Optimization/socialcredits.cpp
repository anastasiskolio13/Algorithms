#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#define MAXN 100000
#define MAXK 2000
using namespace std;

set<pair<int, int>> S;
vector<int> A(MAXN);
vector<int> P(MAXN);
vector<int> TreeOne(4 * MAXN);
vector<int> TreeTwo(4 * MAXN);
vector<vector<int>> dp(MAXN, vector<int>(MAXK + 1));
int N;
int K;

void Update(vector<int>& Tree, int lo, int hi, int v, int i, int x) {
	if (lo == hi) {
		Tree[v] = x;
		return;
	}
	int mid = (lo + hi) / 2;
	if (i <= mid)
		Update(Tree, lo, mid, 2 * v + 1, i, x);
	else
		Update(Tree, mid + 1, hi, 2 * v + 2, i, x);
	Tree[v] = max(Tree[2 * v + 1], Tree[2 * v + 2]);
}

int Query(vector<int>& Tree, int lo, int hi, int v, int qlo, int qhi) {
	if (qlo <= lo && hi <= qhi)
		return Tree[v];
	if (qlo > hi || qhi < lo)
		return 0;
	int mid = (lo + hi) / 2;
	int maximumLeft = Query(Tree, lo, mid, 2 * v + 1, qlo, qhi);
	int maximumRight = Query(Tree, mid + 1, hi, 2 * v + 2, qlo, qhi);
	return max(maximumLeft, maximumRight);
}

int main() {
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; ++i) {
		scanf("%d", &A[i]);
		S.insert({ A[i], i });
	}
	int i = 0;
	for (auto [_, index] : S)
		P[index] = i++;
	for (int i = N - 1; i >= 0; --i) {
		auto it = S.upper_bound({ A[i], N });
		dp[i][K] = it != S.end() ? Query(TreeOne, 0, N - 1, 0, P[it->second], N - 1) + 1 : 1;
		Update(TreeOne, 0, N - 1, 0, P[i], dp[i][K]);
	}
	for (int j = K - 1; j >= 0; --j) {
		TreeTwo = TreeOne;
		fill(TreeOne.begin(), TreeOne.begin() + 4 * N, 0);
		for (int i = N - 1; i >= 0; --i) {
			auto it = S.upper_bound({ A[i], N });
			dp[i][j] = Query(TreeTwo, 0, N - 1, 0, 0, P[(--it)->second]) + 1;
			if ((++it) != S.end())
				dp[i][j] = max(dp[i][j], Query(TreeOne, 0, N - 1, 0, P[it->second], N - 1) + 1);
			Update(TreeOne, 0, N - 1, 0, P[i], dp[i][j]);
		}
	}
	printf("%d\n", Query(TreeOne, 0, N - 1, 0, 0, N - 1));
}