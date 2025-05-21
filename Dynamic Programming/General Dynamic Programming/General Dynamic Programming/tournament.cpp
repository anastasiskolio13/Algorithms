#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXX 1000000
#define MOD 1000000007
using namespace std;

vector<int> P;
vector<vector<int>> dp(MAXX + 1, vector<int>(20));
vector<int> PS(MAXX + 1);
int Q;

void ComputePowers() {
	int p = 1; // 2^0.
	while (p <= MAXX) {
		P.push_back(p);
		p *= 2;
	}
}

void ComputeDP() {
	for (int i = 0; i < 20; ++i)
		dp[0][i] = 1;
	for (int x = 1; x <= MAXX; ++x) {
		dp[x][0] = dp[x - 1][1];
		for (int i = 1; i < 18; ++i) {
			dp[x][i] = dp[x - 1][1];
			if (P[i] <= x) 
				dp[x][i] = ((long long)dp[x][i] + dp[x - P[i]][i + 1]) % MOD;
		}
	}
}

void ComputePrefixSums() {
	PS[0] = dp[0][0];
	for (int x = 1; x <= MAXX; ++x)
		PS[x] = ((long long)PS[x - 1] + dp[x][0]) % MOD;
}

long long Query(int A, int B) {
	return (long long)PS[B] - (A >= 1) * (PS[A - 1]);
}

int main() {
	//freopen("tournament.in", "r", stdin);
	//freopen("tournament.out", "w", stdout);
	ComputePowers();
	ComputeDP();
	ComputePrefixSums();
	scanf("%d", &Q);
	while (Q--) {
		int A, B;
		scanf("%d %d", &A, &B);
		printf("%lld\n",  (long long)((2 * Query(A, B)) % MOD - !A));
	}
}