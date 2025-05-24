#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 10000
#define MAXT 50000
#define MAXX 2000
using namespace std;

struct query {
	int L;
	int R;
	int X;
	int idx;
};

vector<int> C(MAXN);
vector<int> S(MAXN);
vector<long long> B(MAXT);
vector<vector<long long>> dpLeft(MAXN, vector<long long>(MAXX + 1));
vector<vector<long long>> dpRight(MAXN, vector<long long>(MAXX + 1));
int N;
int T;

void DivideAndConquer(int lo, int hi, vector<query> Q) {
	if (lo == hi) {
		for (int i = 0; i < Q.size(); ++i)
			B[Q[i].idx] = S[lo] * (C[lo] > Q[i].X);
		return;
	}
	int mid = (lo + hi) / 2;
	for (int x = 1; x <= MAXX; ++x)
		dpLeft[mid + 1][x] = 0;
	for (int i = )
	for (int i = mid; i >= lo; --i) {
		for (int x = 1; x <= MAXX; ++x) {
			dpLeft[i][x] = dpLeft[i + 1][x];
			if (C[i] <= x)
				dpLeft[i][x] = max(dpLeft[i][x], dpLeft[i + 1][x - C[i]]);
		}
	}
	for (int i = mid + 1; i <= hi; ++i) {

	}
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
		scanf("%d %d", &C[i], &S[i]);
	scanf("%d", &T);
	vector<query> Q(T);
	for (int i = 0; i < T; ++i) {
		scanf("%d %d %d", &Q[i].L, &Q[i].R, &Q[i].X);
		Q[i].idx = i;
	}
}