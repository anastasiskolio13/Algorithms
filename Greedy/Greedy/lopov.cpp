#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#define MAXN 300000
#define MAXK 300000
using namespace std;

struct jewel {
	int M;
	int V;
};

bool compareJewelry(jewel A, jewel B) {
	return A.V > B.V || A.V == B.V && A.M < B.M;
}

multiset<int> S;
vector<jewel> J(MAXN);
vector<int> C(MAXK);
int N;
int K;

int main() {
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; ++i)
		scanf("%d %d", &J[i].M, &J[i].V);
	for (int i = 0; i < K; ++i) {
		scanf("%d", &C[i]);
		S.insert(C[i]);
	}
	sort(J.begin(), J.begin() + N, compareJewelry);
	long long totalValue = 0;
	for (int i = 0; i < N; ++i) {
		auto it = S.lower_bound(J[i].M);
		if (it != S.end()) {
			totalValue += J[i].V;
			S.erase(it);
		}
	}
	printf("%lld\n", totalValue);
}