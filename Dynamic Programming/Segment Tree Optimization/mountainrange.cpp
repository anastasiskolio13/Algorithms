#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#define MAXN 200000
using namespace std;

stack<int> S;
vector<pair<int, int>> A(MAXN + 2);
vector<int> R(MAXN + 1);
vector<int> L(MAXN + 1);
vector<int> dp(MAXN + 1);
vector<int> T(4 * MAXN + 1);
int N;

void Update(int lo, int hi, int v, int i) {
	if (lo == hi) {
		T[v] = dp[i];
		return;
	}
	int mid = (lo + hi) / 2;
	if (i <= mid)
		Update(lo, mid, 2 * v, i);
	else
		Update(mid + 1, hi, 2 * v + 1, i);
	T[v] = max(T[2 * v], T[2 * v + 1]);
}

int Query(int lo, int hi, int v, int qlo, int qhi) {
	if (qlo <= lo && hi <= qhi)
		return T[v];
	if (qlo > hi || qhi < lo)
		return 0;
	int mid = (lo + hi) / 2;
	int maxLeft = Query(lo, mid, 2 * v, qlo, qhi);
	int maxRight = Query(mid + 1, hi, 2 * v + 1, qlo, qhi);
	return max(maxLeft, maxRight);
}

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) {
		scanf("%d", &A[i].first);
		A[i].second = i;
	}
	A[0].first = A[N + 1].first = 1e9 + 1;
	for (int j = 1; j <= N + 1; ++j) {
		while (!S.empty() && A[S.top()].first <= A[j].first) {
			int i = S.top();
			S.pop();
			R[i] = j - 1;
		}
		S.push(j);
	}
	S.pop();
	for (int j = N; j >= 0; --j) {
		while (!S.empty() && A[S.top()].first <= A[j].first) {
			int i = S.top();
			S.pop();
			L[i] = j + 1;
		}
		S.push(j);
	}
	sort(A.begin() + 1, A.begin() + N + 1);
	for (int i = 1; i <= N; ++i) {
		dp[A[i].second] = max(Query(1, N, 1, L[A[i].second], A[i].second - 1), Query(1, N, 1, A[i].second + 1, R[A[i].second])) + 1;
		Update(1, N, 1, A[i].second);
	}
	printf("%d\n", *max_element(dp.begin() + 1, dp.begin() + N + 1));
}