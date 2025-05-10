#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#define INF INT_MAX
#define MAXN 1000000
using namespace std;

vector<int> A(MAXN);
vector<int> PM(MAXN);
int N;
int K;

int MaxKSum(int lo, int hi) {
	if (lo == hi)
		return A[lo];
	int mid = (lo + hi) / 2;
	int maxLeft = MaxKSum(lo, mid);
	int maxRight = MaxKSum(mid + 1, hi);
	int sum = A[mid + 1];
	PM[mid + 1] = sum;
	for (int i = mid + 2; i <= min(i + K - 2, hi); ++i) {
		sum += A[i];
		PM[i] = max(PM[i - 1], sum);
	}
	int maxCombined = -INF;
	sum = 0;
	for (int i = mid; i >= max(mid - K + 1, lo); --i) {
		sum += A[i];
		maxCombined = max(maxCombined, PM[min(i + K - 1, hi)] - sum);
	}
	return max({ maxLeft, maxRight, maxCombined });
}

int main() {
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; ++i)
		scanf("%d", &A[i]);
	printf("%d\n", max(0, MaxKSum(0, N - 1)));
}