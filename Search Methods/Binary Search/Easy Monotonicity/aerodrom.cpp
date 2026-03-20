#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 100000
using namespace std;

vector<int> T(MAXN);
int N;
int M;

long long totalPeopleThatCanBeServedWithin(long long E) {
	long long totalPeople = 0;
	for (int i = 0; i < N; ++i)
		totalPeople += E / T[i];
	return totalPeople;
}

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; ++i)
		scanf("%d", &T[i]);
	long long lo = 1;
	long long hi = 1e14;
	while (lo < hi) {
		long long mid = (lo + hi) / 2;
		if (totalPeopleThatCanBeServedWithin(mid) >= M)
			hi = mid;
		else
			lo = mid + 1;
	}
	printf("%lld\n", lo);
}