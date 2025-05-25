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
			B[Q[i].idx] = S[lo] * (C[lo] <= Q[i].X);
		return;
	}
	int mid = (lo + hi) / 2;
	for (int x = 0; x <= MAXX; ++x)
		dpLeft[mid + 1][x] = 0;
	for (int i = lo; i <= mid; ++i)
		dpLeft[i][0] = 0;
	for (int i = mid; i >= lo; --i) {
		for (int x = 1; x <= MAXX; ++x) {
			dpLeft[i][x] = dpLeft[i + 1][x];
			if (C[i] <= x)
				dpLeft[i][x] = max(dpLeft[i][x], dpLeft[i + 1][x - C[i]] + S[i]);
		}
	}
	for (int x = 0; x <= MAXX; ++x)
		dpRight[mid][x] = 0;
	for (int i = mid + 1; i <= hi; ++i)
		dpRight[i][0] = 0;
	for (int i = mid + 1; i <= hi; ++i) {
		for (int x = 1; x <= MAXX; ++x) {
			dpRight[i][x] = dpRight[i - 1][x];
			if (C[i] <= x)
				dpRight[i][x] = max(dpRight[i][x], dpRight[i - 1][x - C[i]] + S[i]);
		}
	}
	vector<query> QL;
	vector<query> QR;
	for (int i = 0; i < Q.size(); ++i) {
		if (Q[i].L <= mid && mid < Q[i].R) {
			for (int x = 0; x <= Q[i].X; ++x)
				B[Q[i].idx] = max(B[Q[i].idx], dpLeft[Q[i].L][x] + dpRight[Q[i].R][Q[i].X - x]);
		}
		else if (Q[i].R <= mid) {
			QL.push_back(Q[i]);
		}
		else {
			QR.push_back(Q[i]);
		}
	}
	DivideAndConquer(lo, mid, QL);
	DivideAndConquer(mid + 1, hi, QR);
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
		scanf("%d %d", &C[i], &S[i]);
	scanf("%d", &T);
	vector<query> Q(T);
	for (int i = 0; i < T; ++i) {
		scanf("%d %d %d", &Q[i].L, &Q[i].R, &Q[i].X);
		--Q[i].L;
		--Q[i].R;
		Q[i].idx = i;
	}
	DivideAndConquer(0, N - 1, Q);
	for (int i = 0; i < T; ++i) 
		printf("%lld\n", B[i]);
}