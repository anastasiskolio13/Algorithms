#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 100000
using namespace std;

vector<int> A(MAXN);
vector<vector<int>> dp(MAXN, vector<int>(2));
int N;
int K;

int main() {
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; ++i)
		scanf("%d", &A[i]);
	for (int i = N - 1; i >= 0; --i) {
		dp[i][K % 2] = 1;
		for (int k = i + 1; k < N; ++k)
			if (A[k] > A[i])
				dp[i][K % 2] = max(dp[i][K % 2], dp[k][K % 2] + 1);
	}
	for (int j = K - 1; j >= 0; --j) {
		for (int i = N - 1; i >= 0; --i) {
			dp[i][j % 2] = 1;
			for (int k = i + 1; k < N; ++k) 
				if (A[k] > A[i])
					dp[i][j % 2] = max(dp[i][j % 2], dp[k][j % 2] + 1);
				else
					dp[i][j % 2] = max(dp[i][j % 2], dp[k][(j + 1) % 2] + 1);
		}
	}
	int maximumNumberOfPeople = 0;
	for (int i = 0; i < N; ++i)
		maximumNumberOfPeople = max(maximumNumberOfPeople, dp[i][0]);
	printf("%d\n", maximumNumberOfPeople);
}