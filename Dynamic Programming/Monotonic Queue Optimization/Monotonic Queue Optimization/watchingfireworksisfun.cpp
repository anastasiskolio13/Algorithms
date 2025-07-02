#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cmath>
#include <deque>
#define MAXN 150000
#define MAXM 300
using namespace std;

vector<int> A(MAXM + 1);
vector<int> B(MAXM + 1);
vector<int> T(MAXM + 1);
vector<vector<long long>> dp(2, vector<long long>(MAXN + 1));
int N;
int M;
int D;

int main() {
	scanf("%d %d %d", &N, &M, &D);
	for (int i = 1; i <= M; ++i)
		scanf("%d %d %d", &A[i], &B[i], &T[i]);
	T[0] = 1;
	for (int i = 1; i <= N; ++i)
		dp[M % 2][i] = B[M] - abs(A[M] - i);
	for (int j = M - 1; j >= 0; --j) {
		deque<int> Q;
		for (int i = ; i >= 1; --i) {
			if (i < min(N, i + (T[i + 1] - T[i]) * D))
				Q.pop_front();
			dp[i] = 
		}
	}
}