#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <stack>
#define MAXN 300000
#define INF 1e14
using namespace std;

stack<int> Q;
vector<int> H(MAXN + 1);
vector<int> B(MAXN);
vector<int> P(MAXN);
vector<int> S(MAXN);
vector<long long> M(MAXN);
vector<int> R(MAXN);
vector<long long> T(4 * (MAXN + 1) + 1);
vector<long long> dp(MAXN + 1);
int N;

void DSU() {
	for (int a = 0; a < N; ++a) {
		P[a] = a;
		S[a] = 1;
		M[a] = -INF;
	}
}

int Find(int a) {
	return a == P[a] ? a : P[a] = Find(P[a]);
}

void Unite(int a, int b) {
	a = Find(a);
	b = Find(b);
	if (S[b] > S[a])
		swap(a, b);
	P[b] = a;
	S[a] += S[b];
}

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

long long Query(int lo, int hi, int v, int qlo, int qhi) {
	if (qlo <= lo && hi <= qhi)
		return T[v];
	if (qlo > hi || qhi < lo)
		return -INF;
	int mid = (lo + hi) / 2;
	long long maxLeft = Query(lo, mid, 2 * v, qlo, qhi);
	long long maxRight = Query(mid + 1, hi, 2 * v + 1, qlo, qhi);
	return max(maxLeft, maxRight);
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
		scanf("%d", &H[i]);
	H[N] = -2e9;
	for (int i = 0; i < N; ++i)
		scanf("%d", &B[i]);
	DSU();
	for (int i = 0; i <= N; ++i) {
		while (!Q.empty() && H[i] < H[Q.top()]) {
			int j = Q.top();
			Q.pop();
			R[j] = i - 1;
			if (i != N)
				Unite(j, i);
		}
		Q.push(i);
	}
	for (int i = N - 1; i >= 0; --i) {
		long long maximumValue = max(Query(0, N, 1, i + 1, R[i] + 1) + B[i], M[Find(i)]);
		dp[i] = M[P[i] /*Find(i)*/] = maximumValue;
		Update(0, N, 1, i);
	}
	/*for (int i = N - 1; i >= 0; --i) {
		int argMinHeight = i;
		dp[i] = -2e9;
		for (int j = i; j < N; ++j) {
			if (H[j] < H[argMinHeight])
				argMinHeight = j;
			dp[i] = max(dp[i], dp[j + 1] + B[argMinHeight]);
		}

	}*/
	printf("%lld\n", dp[0]);
}