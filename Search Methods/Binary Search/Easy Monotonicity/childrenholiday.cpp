#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <numeric>
#define MAXN 1000
using namespace std;

vector<long long> T(MAXN);
vector<long long> Z(MAXN);
vector<long long> Y(MAXN);
vector<long long> B(MAXN);
long long N;
long long M;

long long totalBalloonsInflatedInTime(long long E) {
	for (int i = 0; i < N; ++i) {
		long long rounds = (E + Y[i]) / (Z[i] * T[i] + Y[i]);
		B[i] = Z[i] * rounds;
		long long remainingTime = E - rounds * (Z[i] * T[i] + Y[i]);
		if (remainingTime > 0)
			B[i] += remainingTime / T[i];
	}
	return accumulate(B.begin(), B.begin() + N, 0LL);
}

int main() {
	scanf("%lld %lld", &M, &N);
	for (int i = 0; i < N; ++i)
		scanf("%lld %lld %lld", &T[i], &Z[i], &Y[i]);
	long long lo = 0;
	long long hi = 2e9;
	while (lo < hi) {
		long long mid = (lo + hi) / 2;
		if (totalBalloonsInflatedInTime(mid) >= M)
			hi = mid;
		else
			lo = mid + 1;
	}
	printf("%lld\n", lo);
	totalBalloonsInflatedInTime(lo);
	long long toGive = M;
	for (int i = 0; i < N; ++i) {
		long long give = min(toGive, B[i]);
		printf("%lld ", give);
		toGive -= give;
	}
}