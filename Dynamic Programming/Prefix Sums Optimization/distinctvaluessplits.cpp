#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <map>
#define MAXN 200000
#define MOD 1000000007
using namespace std;

map<int, int> C;
vector<int> A(MAXN);
vector<int> R(MAXN);
vector<long long> dp(MAXN + 1);
vector<long long> S(MAXN + 2);
int N;

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
		scanf("%d", &A[i]);
	int differentNumbers = 0;
	int i = N - 1;
	for (int j = N - 1; j >= 0; --j) {
		differentNumbers += !C[A[j]]++;
		while (differentNumbers < i - j + 1)
			differentNumbers -= !--C[A[i--]];
		R[j] = i;
	}
	dp[N] = 1;
	S[N] = 1;
	for (int i = N - 1; i >= 0; --i) {
		dp[i] = ((S[i + 1] - S[R[i] + 2]) % MOD + MOD) % MOD;
		S[i] = (S[i + 1] + dp[i]) % MOD;
	}
	printf("%d\n", dp[0]);
}