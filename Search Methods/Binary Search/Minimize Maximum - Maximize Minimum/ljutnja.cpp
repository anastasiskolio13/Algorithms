#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 100000
using namespace std;

vector<int> A(MAXN);
int M;
int N;

long long candiesNeededToAchieveMaximumDifference(int D) {
	long long candies = 0;
	for (int i = 0; i < N; ++i)
		candies += max(A[i] - D, 0);
	return candies;
}

int main() {
	scanf("%d %d", &M, &N);
	for (int i = 0; i < N; ++i)
		scanf("%d", &A[i]);
	int lo = 1;
	int hi = 2e9;
	while (lo < hi) {
		int mid = lo + (hi - lo) / 2;
		if (candiesNeededToAchieveMaximumDifference(mid) <= M)
			hi = mid;
		else
			lo = mid + 1;
	}
	int remaining = M - candiesNeededToAchieveMaximumDifference(lo);
	long long ans = 0;
	for (int i = 0; i < N; ++i) {
		if (A[i] - lo < 0) {
			ans += (long long)A[i] * A[i];
			continue;
		}
		if (remaining > 0) {
			ans += (long long)(lo - 1) * (lo - 1);
			--remaining;
		}
		else {
			ans += (long long)lo * lo;
		}

	}
	printf("%lld\n", ans);
}