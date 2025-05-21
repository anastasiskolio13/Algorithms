#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
using namespace std;

int T;
int N;
int M;
int K;

long long numberOfKidsSeated(int L) {
	int benchesPerRow = floor((double)(M + 1) / (L + 1));
	int additionalBenchCapacity = max(M - (long long)benchesPerRow * (L + 1), 0LL);
	return N * ((long long)L * benchesPerRow + additionalBenchCapacity);
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d %d", &N, &M, &K);
		int lo = 1;
		int hi = M;
		while (lo < hi) {
			int mid = (lo + hi) / 2;
			if (numberOfKidsSeated(mid) >= K)
				hi = mid;
			else
				lo = mid + 1;
		}
		printf("%d\n", lo);
	}
}