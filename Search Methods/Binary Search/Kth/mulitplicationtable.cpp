#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

long long N;
long long K;

long long countOfElementsAtMost(long long X) {
	long long totalElements = 0;
	for (long long i = 1; i <= N; ++i)
		totalElements += min(X / i, N);
	return totalElements;
}

int main() {
	scanf("%lld %lld", &N, &K);
	long long lo = 1;
	long long hi = N * N;
	while (lo < hi) {
		long long mid = (lo + hi) / 2;
		if (countOfElementsAtMost(mid) >= K)
			hi = mid;
		else
			lo = mid + 1;
	}
	printf("%lld\n", lo);
}