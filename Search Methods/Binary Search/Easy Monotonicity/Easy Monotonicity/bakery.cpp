#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cmath>
#define MAXN 100
using namespace std;

vector<long long> A(MAXN);
vector<long long> B(MAXN);
vector<long long> C(MAXN);
int T;
int N;
long long tM;
long long tC;

bool canBessieSatisfyAllHerFriends(long long L) {
	for (int i = 0; i < N; ++i) {
		double lowerBound = max(0LL, L - tC + 1);
		double upperBound = min(tM - 1, L);
		bool extraConstraint = true;
		if (A[i] > B[i])
			upperBound = min(upperBound, (double)(C[i] - A[i] * (tC - L) - B[i] * tM) / (A[i] - B[i]));
		else if (A[i] < B[i])
			lowerBound = max(lowerBound, (double)(C[i] - A[i] * (tC - L) - B[i] * tM) / (A[i] - B[i]));
		else
			extraConstraint = C[i] - A[i] * (tC - L + tM) >= 0;
		if (ceil(lowerBound) > floor(upperBound) || extraConstraint == false)
			return false;
	}
	return true;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d %d", &N, &tC, &tM);
		for (int i = 0; i < N; ++i)
			scanf("%d %d %lld", &A[i], &B[i], &C[i]);
		int lo = 0;
		int hi = tC + tM - 2;
		while (lo < hi) {
			int mid = lo + (hi - lo) / 2;
			if (canBessieSatisfyAllHerFriends(mid))
				hi = mid;
			else
				lo = mid + 1;
		}
		printf("%d\n", lo);
	}
}
