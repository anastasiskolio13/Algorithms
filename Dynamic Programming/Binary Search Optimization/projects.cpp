#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 200000
using namespace std;

struct segment {
	int A;
	int B;
	int P;
};

bool compareSegments(segment X, segment Y) {
	return X.B < Y.B;
}

vector<segment> S(MAXN + 1);
vector<long long> dp(MAXN + 1);
int N;

int findPrevious(int i) {
	int lo = 0;
	int hi = i - 1;
	while (lo < hi) {
		int mid = (lo + hi + 1) / 2;
		if (S[i].A > S[mid].B)
			lo = mid;
		else
			hi = mid - 1;
	}
	return lo;
}

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i)
		scanf("%d %d %d", &S[i].A, &S[i].B, &S[i].P);
	S[0].A = 0;
	S[0].B = 0;
	S[0].P = 0;
	sort(S.begin(), S.begin() + N + 1, compareSegments);
	dp[0] = 0;
	for (int i = 1; i <= N; ++i) {
		int j = findPrevious(i);
		dp[i] = max(dp[i - 1], dp[j] + S[i].P);
	}
	printf("%lld\n", dp[N]);
}