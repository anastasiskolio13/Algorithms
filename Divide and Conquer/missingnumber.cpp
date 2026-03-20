#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;

int FindMissing(vector<int>& A, int lo, int hi) {
	if (lo == hi)
		return lo;
	int mid = (lo + hi) / 2;
	vector<int> B;
	vector<int> C;
	for (int i = 0; i < A.size() /* hi - lo*/ ; ++i)
		A[i] <= mid ? B.push_back(A[i]) : C.push_back(A[i]);
	if (B.size() < mid - lo + 1)
		return FindMissing(B, lo, mid);
	else
		return FindMissing(C, mid + 1, hi);
}

int main() {
	int N;
	scanf("%d", &N);
	vector<int> A(N - 1);
	for (int i = 0; i < N - 1; ++i)
		scanf("%d", &A[i]);
	printf("%d\n", FindMissing(A, 1, N));
}