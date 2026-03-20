#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <map>
#define MAXN 2000
#define MAXV 100000
#define MAXC 10000
#define INF 2e9
using namespace std;

map<pair<int, int>, vector<int>> M;
vector<int> D(MAXN + 1);
vector<vector<int>> dp(2, vector<int>(MAXC + 1));
vector<int> R(MAXV + 1);
int N;
int V;

int main() {
	scanf("%d %d", &N, &V);
	for (int i = 1; i <= N; ++i)
		scanf("%d", &D[i]);
	for (int i = 1; i <= V; ++i) {
		int C, L;
		scanf("%d %d", &C, &L);
		M[{L, C}].push_back(i);
	}
	dp[0][0] = 0;
	for (int c = 1; c <= MAXC; ++c)
		dp[0][c] = INF;
	for (int i = 1; i <= N; ++i) {
		for (int c = 1; c <= MAXC; ++c) {
			dp[i % 2][c] = dp[(i - 1) % 2][c];
			if (c >= D[i])
				dp[i % 2][c] = min(dp[i % 2][c], dp[i % 2][c - D[i]] + 1);
			if (M.find({ i, c }) == M.end())
				continue;
			for (int index : M[{i, c}])
				R[index] = dp[i % 2][c] != INF ? dp[i % 2][c] : -1;
		}
	}
	for (int i = 1; i <= V; ++i)
		printf("%d\n", R[i]);
}