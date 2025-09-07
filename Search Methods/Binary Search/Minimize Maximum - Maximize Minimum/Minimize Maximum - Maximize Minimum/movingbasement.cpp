#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 200000
using namespace std;

vector<int> P(MAXN);
vector<long long> R(MAXN);
int N;

bool CanAchieve(int K) {
	for (int i = 0; i < N; ++i)
		R[i] = P[i];
	for (int i = N - 1; i >= 2; --i) {
		long long totalOperations = ((long long)R[i] - K) / 3;
		R[i - 1] += totalOperations;
		R[i - 2] += 2 * totalOperations;
		if (R[i] < K)
			return false;
	}
	return R[0] >= K && (R[1] >= K;
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
		scanf("%d", &P[i]);
	int lo = 1;
	int hi = 1000000000;
	while (lo < hi) {
		int mid = (lo + hi + 1) / 2;
		if (CanAchieve(mid))
			lo = mid;
		else
			hi = mid - 1;
	}
	printf("%d\n", lo);
}