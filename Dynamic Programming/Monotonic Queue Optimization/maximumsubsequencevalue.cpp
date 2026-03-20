#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <deque>
#define MAXK 200
#define MAXN 100000
using namespace std;

vector<int> A(MAXN);
vector<vector<long long>> dp(2, vector<long long>(MAXN));
int N;
int M;
int K;

int main() {
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 0; i < N; ++i)
		scanf("%d", &A[i]);
	for (int j = K - 1; j >= 0; --j) {
		deque<int> Q;
		dp[j % 2][N - 1] = (long long)(j + 1) * A[N - 1];
		Q.push_back(N - 1);
		for (int i = N - 2; i >= 0; --i) {
			if (Q.front() == i + M + 1)
				Q.pop_front();
			dp[j % 2][i] = dp[(j + 1) % 2][Q.front()] + (long long)(j + 1) * A[i];
			while (!Q.empty() && dp[(j + 1) % 2][i] >= dp[(j + 1) % 2][Q.back()])
				Q.pop_back();
			Q.push_back(i);
		}
	}
	long long max_dp = dp[0][0];
	for (int i = 1; i < N; ++i)
		max_dp = max(max_dp, dp[0][i]);
	printf("%lld\n", max_dp);
}