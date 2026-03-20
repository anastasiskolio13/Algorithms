#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 5000000
using namespace std;

vector<int> T(MAXN + 1);
vector<long> dp(MAXN + 2);
int S;
int P;
int M;
int N;

int FindNextTrip(int i) {
	int lo = i;
	int hi = N;
	while (lo < hi) {
		int mid = (lo + hi + 1) / 2;
		if (T[i] + M - 1 >= T[mid])
			lo = mid;
		else
			hi = mid - 1;
	}
	return lo;
}

int main() {
	scanf("%d %d %d %d", &S, &P, &M, &N);
	for (int i = 1; i <= N; ++i)
		scanf("%d", &T[i]);
	dp[N + 1] = 0;
	for (int i = N; i >= 1; --i) {
		int j = FindNextTrip(i);
		dp[i] = min(dp[i + 1] + S, dp[j + 1] + P);
	}
	printf("%ld\n", dp[1]);
}