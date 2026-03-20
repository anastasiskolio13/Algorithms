#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 200000
using namespace std;

vector<long long> A(MAXN + 2);
vector<int> counterValue(MAXN + 2);
vector<int> counterValueAfter(MAXN + 2);
vector<pair<long long, long long>> PS(MAXN + 2);
int subproblem;
int N;
int Q;

int FindCounter(int x) {
	int l = 1;
	int r = N;
	int counter = 0;
	while (l <= r) {
		counter = counter + 1;
		int m = (l + r) / 2;
		if (A[m] == x)
			return counter;
		if (A[m] < x)
			l = m + 1;
		if (A[m] > x)
			r = m - 1;
	}
	return counter;
}

long long sumOfCounters(long long l, long long r) {
	auto iteratorOne = lower_bound(A.begin() + 1, A.begin() + N + 1, l);
	auto iteratorTwo = upper_bound(A.begin() + 1, A.begin() + N + 1, r);
	int lb = iteratorOne != A.begin() + N + 1 ? iteratorOne - A.begin() : N + 1;
	int ub = iteratorTwo != A.begin() ? --iteratorTwo - A.begin() : N + 1;
	long long sumOfCountersOfPresentValues = PS[ub].first * (ub != N + 1) - PS[lb - 1].first * (lb != N + 1);
	long long sumOfCountersOfNonPresentValuesOne = PS[ub - 1].second * (ub != N + 1) - PS[lb - 1].second * (lb != N + 1);
	long long sumOfCountersOfNonPresentValuesTwo = (A[lb] - l) * (lb != N + 1) * counterValueAfter[lb - 1] + (r - A[ub]) * (ub != N + 1) * counterValueAfter[ub] +;
	return sumOfCountersOfPresentValues + sumOfCountersOfNonPresentValuesOne + sumOfCountersOfNonPresentValuesTwo;
}

int main() {
	scanf("%d %d %d", &subproblem, &N, &Q);
	for (int i = 1; i <= N; ++i)
		scanf("%lld", &A[i]);
	for (int i = 1; i <= N; ++i) {
		counterValue[i] = FindCounter(A[i]);
		if (i < N && A[i] + 1 < A[i + 1])
			counterValueAfter[i] = FindCounter(A[i] + 1);
	}
	counterValueAfter[0] = FindCounter(A[1] - 1);
	counterValueAfter[N] = FindCounter(A[N] + 1);
	for (int i = 1; i <= N; ++i) {
		PS[i].first = PS[i - 1].first + counterValue[i];
		if (i < N)
			PS[i].second = PS[i - 1].second + counterValueAfter[i] * (A[i + 1] - A[i] - 1);
	}
	while (Q--) {
		long long L, R;
		scanf("%lld", &L, &R);
	}
}