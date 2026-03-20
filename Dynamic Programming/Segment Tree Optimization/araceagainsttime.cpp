#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <stack>
#define MAXN 100000
#define INF 1e16
using namespace std;

stack<int> S;
vector<int> H(MAXN + 1);
vector<int> P(MAXN + 1);
vector<int> R(MAXN);
vector<long long> T(4 * (MAXN + 1) + 1);
vector<long long> dp(MAXN + 1);
int N;

void Update(int lo, int hi, int v, int i) {
	if (lo == hi) {
		T[v] = dp[i] - H[i] + i + P[i];
		return;
	}
	int mid = (lo + hi) / 2;
	if (i <= mid)
		Update(lo, mid, 2 * v, i);
	else
		Update(mid + 1, hi, 2 * v + 1, i);
	T[v] = min(T[2 * v], T[2 * v + 1]);
}

long long Query(int lo, int hi, int v, int qlo, int qhi) {
	if (qlo <= lo && hi <= qhi)
		return T[v];
	if (qlo > hi || qhi < lo)
		return INF;
	int mid = (lo + hi) / 2;
	long long minLeft = Query(lo, mid, 2 * v, qlo, qhi);
	long long minRight = Query(mid + 1, hi, 2 * v + 1, qlo, qhi);
	return min(minLeft, minRight);
}

int main() {
	scanf("%d %d", &N, &H[0]);
	for (int i = 1; i < N; ++i)
		scanf("%d", &H[i]);
	H[N] = 2e9;
	for (int i = 1; i < N; ++i)
		scanf("%d", &P[i]);
	for (int j = 0; j <= N; ++j) {
		while (!S.empty() && H[j] > H[S.top()]) {
			int i = S.top();
			S.pop();
			R[i] = j;
		}
		S.push(j);
	}
	H[N] = 0;
	dp[N] = 0;
	Update(0, N, 1, N);
	for (int i = N - 1; i >= 0; --i) {
		dp[i] = min(Query(0, N, 1, i + 1, R[i] - 1) + H[i] - i, dp[R[i]] + (R[i] == N ? 0 : H[R[i]] - H[i]) + R[i] - i + P[R[i]]);
		Update(0, N, 1, i);
	}
	printf("%lld\n", dp[0]);
}