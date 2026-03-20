#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <deque>
#define MAXN 100000
#define INF 1e6
using namespace std;

deque<int> minQ;
deque<int> maxQ;
vector<int> A(MAXN);
vector<int> R(MAXN);
vector<int> dp(MAXN + 1);
vector<int> T(4 * MAXN + 1);
int N;
int S;
int L;

void PushToQueues(int i) {
	while (!minQ.empty() && A[i] <= A[minQ.back()])
		minQ.pop_back();
	minQ.push_back(i);
	while (!maxQ.empty() && A[i] >= A[maxQ.back()])
		maxQ.pop_back();
	maxQ.push_back(i);
}

void PopFromQueues(int i) {
	if (i == minQ.front())
		minQ.pop_front();
	if (i == maxQ.front())
		maxQ.pop_front();
}

void Update(int lo, int hi, int v, int i) {
	if (lo == hi) {
		T[v] = dp[i];
		return;
	}
	int mid = (lo + hi) / 2;
	if (i <= mid)
		Update(lo, mid, 2 * v + 1, i);
	else
		Update(mid + 1, hi, 2 * v + 2, i);
	T[v] = min(T[2 * v + 1], T[2 * v + 2]);
}

int Query(int lo, int hi, int v, int qlo, int qhi) {
	if (qlo <= lo && hi <= qhi)
		return T[v];
	if (qlo > hi || qhi < lo)
		return INF;
	int mid = (lo + hi) / 2;
	int minLeft = Query(lo, mid, 2 * v + 1, qlo, qhi);
	int minRight = Query(mid + 1, hi, 2 * v + 2, qlo, qhi);
	return min(minLeft, minRight);
}

int main() {
	scanf("%d %d %d", &N, &S, &L);
	for (int i = 0; i < N; ++i)
		scanf("%d", &A[i]);
	int i = N - 1;
	for (int j = N - 1; j >= 0; --j) {
		PushToQueues(j);
		while (A[maxQ.front()] - A[minQ.front()] > S)
			PopFromQueues(i--);
		R[j] = i;
	}
	Update(0, N, 0, N);
	for (int i = N - 1; i >= 0; --i) {
		dp[i] = i + L <= R[i] + 1 ? Query(0, N, 0, i + L, R[i] + 1) + 1 : INF;
		Update(0, N, 0, i);
	}
	printf("%d\n", dp[0] >= INF ? -1 : dp[0]);
}