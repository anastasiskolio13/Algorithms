#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <deque>
#define MAXN 100000
#define INF 1e6
using namespace std;

deque<int> minQ;
deque<int> maxQ;
deque<int> Q;
vector<int> A(MAXN);
vector<int> R(MAXN);
vector<int> dp(MAXN + 1);
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
	dp[N] = 0;
	Q.push_back(N);
	for (int i = N - 1; i >= 0; --i) {
		while (Q.front() > R[i] + 1)
			Q.pop_front();
		dp[i] = Q.front() >= i + L ? dp[Q.front()] + 1 : INF;
		while (!Q.empty() && dp[i] < dp[Q.back()])
			Q.pop_back();
		Q.push_back(i);
	}
	printf("%d\n", dp[0] >= INF ? -1 : dp[0]);
}