#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#define MAXN 200000
#define INF LONG_MAX
using namespace std;

vector<int> A(MAXN);
int N;

long DivideAndConquer(int lo, int hi) {
	if (lo == hi)
		return A[lo];
	int mid = (lo + hi) / 2;
	long maximumSubarrayLeft = DivideAndConquer(lo, mid);
	long maximumSubarrayRight = DivideAndConquer(mid + 1, hi);
	long sumLeft = 0;
	long maximumSumLeft = -INF;
	for (int i = mid; i >= lo; --i) {
		sumLeft += A[i];
		maximumSumLeft = max(maximumSumLeft, sumLeft);
	}
	long sumRight = 0;
	long maximumSumRight = -INF;
	for (int i = mid + 1; i <= hi; ++i) {
		sumRight += A[i];
		maximumSumRight = max(maximumSumRight, sumRight);
	}
	return max({ maximumSubarrayLeft, maximumSumLeft + maximumSumRight, maximumSubarrayRight });
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
		scanf("%d", &A[i]);
	printf("%ld\n", DivideAndConquer(0, N - 1));
}