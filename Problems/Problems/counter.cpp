#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 200000
using namespace std;

vector<long long> A(MAXN);
vector<int> iterationsToFindElement(MAXN);
vector<int> iterationsToFindAnElementAfter(MAXN - 1);
int subproblem;
int N;
int Q;
long long L;
long long R;

int FindCounter(long long X) {
	int lo = 0;
	int hi = N - 1;
	int counter = 0;
	while (lo <= hi) {
		++counter;
		int mid = (lo + hi) / 2;
		if (A[mid] == X)
			return counter;
		else if (A[mid] < X)
			lo = mid + 1;
		else
			hi = mid - 1;
	}
	return counter;
}

int main() {
	scanf("%d", &subproblem);
	scanf("%d %d", &N, &Q);

	for (int i = 0; i < N; ++i) {
		scanf("%lld", &A[i]);
		iterationsToFindElement[i] = FindCounter(A[i]);
	}

	for (int i = 0; i < N - 1; ++i)
		iterationsToFindAnElementAfter[i] = FindCounter(A[i] + 1) * (A[i] + 1 < A[i + 1]);
		
	while (Q--) {
		scanf("%lld %lld", &L, &R);
	}
}