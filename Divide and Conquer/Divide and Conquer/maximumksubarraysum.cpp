#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 1000000
#define INF 1e9
using namespace std;

vector<int> A(MAXN);
vector<int> S(MAXN);
int N;
int K;

int DivideAndConquer(int lo, int hi) {
	if (lo == hi)
		return A[lo];
	int mid = (lo + hi) / 2;
	int maximumKSubarrayLeft = DivideAndConquer(lo, mid);
	int maximumKSubarrayRight = DivideAndConquer(mid + 1, hi);
	int sumRight = 0;
	S[mid] = -INF;
	for (int i = mid + 1; i <= min(mid + K - 1, hi); ++i) {
		sumRight += A[i];
		S[i] = max(S[i - 1], sumRight);
	}
	int sumLeft = 0;
	int maximumKSubarrayCombined = -INF;
	for (int i = mid; i >= max(mid - K + 1, lo); --i) {
		sumLeft += A[i];
		maximumKSubarrayCombined = max(maximumKSubarrayCombined, sumLeft + S[min(i + K - 1, hi)]);
	}
	return max({ maximumKSubarrayLeft, maximumKSubarrayCombined, maximumKSubarrayRight });
}

int main() {
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; ++i)
		scanf("%d", &A[i]);
	printf("%d\n", max(DivideAndConquer(0, N - 1), 0));
}