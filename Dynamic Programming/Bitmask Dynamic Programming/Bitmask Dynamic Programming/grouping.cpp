#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 16
using namespace std;

vector<vector<int>> A(MAXN, vector<int>(MAXN));
vector<long long> C(1 << MAXN);
vector<long long> dp(1 << MAXN);
int N;

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			scanf("%d", &A[i][j]);
	for (int s = 0; s < (1 << N); ++s) {
		for (int i = 0; i < N; ++i) {
			if (!(s & (1 << i)))
				continue;
			for (int j = i + 1; j < N; ++j)
				if (s & (1 << j))
					C[s] += A[i][j];
		}
	}
	dp[0] = 0;
	for (int s = 1; s < (1 << N); ++s) {

	}
	printf("%lld\n", dp[(1 << N) - 1]);
}