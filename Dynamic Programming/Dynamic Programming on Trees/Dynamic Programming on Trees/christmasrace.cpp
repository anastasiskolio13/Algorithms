#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 8000 // 80%.
using namespace std;

vector<int> A(MAXN);
vector<int> B(MAXN);
vector<pair<int, int>> C(MAXN);
vector<vector<long long>> dp(MAXN, vector<long long>(MAXN));
int N;

long long s(int v, int u) {
	if (dp[v][u] != -1)
		return dp[v][u];
	if (v == 0)
		return dp[v][u] = 0;
	int p_v = C[v].first;
	int d = C[v].second;
	return dp[v][u] = min(s(p_v, u) + d * B[u], s(p_v, v) + A[v] + d * B[v]);
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N - 1; ++i) {
		int p_v, v, d;
		scanf("%d %d %d", &p_v, &v, &d);
		C[--v] = { --p_v, d };
	}
	for (int v = 1; v < N; ++v)
		scanf("%d %d", &A[v], &B[v]);
	for (int v = 0; v < N; ++v)
		for (int v = 0; v < N; ++v)
			dp[v][v] = -1;
	for (int v = 1; v < N; ++v)
		printf("%lld ", s(v, v) + A[v]);
}

5
1
2
20
2
3
12
2
4
1
4
5
3
26
9
1
10
500
2
2
30