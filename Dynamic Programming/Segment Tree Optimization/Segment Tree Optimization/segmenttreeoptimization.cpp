#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 200000
#define INF 1e18
using namespace std;

vector<int> A(MAXN + 1);
vector<int> L(MAXN + 1);
vector<int> R(MAXN + 1);
vector<long long> PS(MAXN + 1);
vector<long long> dp(MAXN + 1);
vector<long long> T(4 * MAXN + 1);
int N;

void Update(int lo, int hi, int v, int i) {
	if (lo == hi) {
		T[v] = dp[i] - PS[i - 1];
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
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) {
		scanf("%d", &A[i]);
		PS[i] = PS[i - 1] + A[i];
	}
	for (int i = 2; i <= N; ++i)
		scanf("%d %d", &L[i], &R[i]);
	// Calculate DP.
	dp[1] = 0;
	for (int i = 2; i <= N; ++i) {
		dp[i] = Query(1, N, 1, L[i], R[i]) + PS[i];
		Update(1, N, 1, i);
	}
	// Print output.
	for (int i = 1; i <= N; ++i)
		printf("%lld ", dp[i]);
}