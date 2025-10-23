#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#define MAXN 500000
using namespace std;

set<pair<long long, int>> S;
vector<int> A(MAXN + 1);
vector<long long> B(MAXN + 1);
vector<long long> PS(MAXN + 1);
vector<long long> T(4 * MAXN);
vector<int> I(MAXN + 1);
int N;

void Update(int lo, int hi, int v, int i) {
	if (lo == hi) {
		T[v] = 1;
		return;
	}
	int mid = (lo + hi) / 2;
	if (I[i] <= mid)
		Update(lo, mid, 2 * v + 1, i);
	else
		Update(mid + 1, hi, 2 * v + 2, i);
	T[v] = T[2 * v + 1] + T[2 * v + 2];
}

int Query(int lo, int hi, int v, int qlo, int qhi) {
	if (qlo <= lo && hi <= qhi)
		return T[v];
	if (qlo > hi || qhi < lo)
		return 0;
	int mid = (lo + hi) / 2;
	int sumLeft = Query(lo, mid, 2 * v + 1, qlo, qhi);
	int sumRight = Query(mid + 1, hi, 2 * v + 2, qlo, qhi);
	return sumLeft + sumRight;
}

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) {
		scanf("%d", &A[i]);
		PS[i] = PS[i - 1] + A[i];
	}
	for (int i = 1; i <= N; ++i) {
		scanf("%lld", &B[i]);
		S.insert({ PS[i] - B[i], i });
	}
	int i = 0;
	for (auto [_, index] : S)
		I[index] = i++;
	int ans = 0;
	for (int i = N; i >= 1; --i) {
		Update(0, N - 1, 0, i);
		auto iteratorOne = S.lower_bound({ PS[i - 1], 0 });
		if (iteratorOne != S.end())
			ans = max(ans, Query(0, N - 1, 0, I[iteratorOne->second], N - 1));
	}
	printf("%d\n", ans);
}