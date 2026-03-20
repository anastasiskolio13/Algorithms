#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 100000
#define MAXM 100000
using namespace std;

vector<int> L(MAXN);
vector<int> R(MAXM);
int N;
int M;

// Maximizing the number of pairs with a greedy algorithm using two pointers method. 
int totalPairsFormedWithMaximumDifferrence(int D) {
	int totalPairs = 0;
	int j = 0;
	for (int i = 0; i < N; ++i) {
		while (j < M && R[j] < L[i] - D)
			++j;
		if (j < M && R[j] <= L[i] + D) {
			++totalPairs;
			++j;
		}
	}
	return totalPairs;
}

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; ++i)
		scanf("%d", &L[i]);
	for (int i = 0; i < M; ++i)
		scanf("%d", &R[i]);
	sort(L.begin(), L.begin() + N);
	sort(R.begin(), R.begin() + M);
	// Binary Search the answer.
	int lo = 0;
	int hi = max(R[M - 1] - L[0], L[N - 1] - R[0]);
	while (lo < hi) {
		int mid = (lo + hi) / 2;
		if (totalPairsFormedWithMaximumDifferrence(mid) >= min(N, M))
			hi = mid;
		else
			lo = mid + 1;
	}
	printf("%d\n", lo);
}