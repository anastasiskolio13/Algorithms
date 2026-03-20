#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#define MAXN 200000
#define MAXM 200000
using namespace std;

struct voucher {
	int L;
	int D;
};

bool compareVouchers(voucher A, voucher B) {
	return A.D > B.D || A.D == B.D && A.L < B.L;
}

multiset<int> S;
vector<int> P(MAXN);
vector<voucher> V(MAXM);
int N;
int M;

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; ++i) {
		scanf("%d", &P[i]);
		S.insert(P[i]);
	}
	for (int i = 0; i < M; ++i)
		scanf("%d", &V[i].L);
	for (int i = 0; i < M; ++i)
		scanf("%d", &V[i].D);
	sort(V.begin(), V.begin() + M, compareVouchers);
	long long minimumTotalCost = 0;
	for (int i = 0; i < M; ++i) {
		auto it = S.lower_bound(V[i].L);
		if (it != S.end()) {
			minimumTotalCost += *it - V[i].D;
			S.erase(it);
		}
	}
	for (int itemPrice : S)
		minimumTotalCost += itemPrice;
	printf("%lld\n", minimumTotalCost);
}