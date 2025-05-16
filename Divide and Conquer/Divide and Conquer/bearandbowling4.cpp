#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#define MAXN 200000
#define INF LLONG_MAX
using namespace std;

vector<int> A(MAXN + 1);
vector<pair<long long, long long>> PS(MAXN + 1);
vector<long long> P(MAXN + 1);
int N;

long long C(int i, int j) {
	return PS[j].second - PS[i - 1].second - i * (PS[j].first - PS[i - 1].first) + PS[j].first - PS[i - 1].first;
}

void DivideAndConquer(int lo, int hi, int opt_lo, int opt_hi) {
	if (lo > hi)
		return;
	int mid = (lo + hi) / 2;
	P[mid] = -INF;
	int opt_i;
	for (int i = opt_lo; i <= min(opt_hi, mid); ++i) {
		if (C(i, mid) > P[mid]) {
			P[mid] = C(i, mid);
			opt_i = i;
		}
	}
	DivideAndConquer(lo, mid - 1, opt_lo, opt_i);
	DivideAndConquer(mid + 1, hi, opt_i, opt_hi);
}

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) {
		scanf("%d", &A[i]);
		PS[i].first = PS[i - 1].first + A[i];
		PS[i].second = PS[i - 1].second + (long long)A[i] * i;
	}
	DivideAndConquer(1, N, 1, N);
	printf("%lld\n", max(*max_element(P.begin() + 1, P.begin() + N + 1), 0LL));
}