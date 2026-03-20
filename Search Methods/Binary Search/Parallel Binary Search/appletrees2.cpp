#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#define MAXN 100000
#define MAXQ 100000
using namespace std;

vector<int> A(MAXN);
vector<int> B(MAXN);
vector<pair<int, int>> R(MAXN);
vector<array<int, 3>> U(MAXQ);
vector<vector<int>> TS(MAXN);
int N;
int Q;

class LazySegmentTree {
private:
	vector<long long> T;
	vector<long long> L;
	vector<bool> F;
public:
	LazySegmentTree(const int N) {
		T.resize(4 * N, 0);
		L.resize(4 * N, 0);
		F.resize(4 * N, true);
	}

	void Relax(const int lo, const int hi, const int v) {
		if (!F[v]) {
			T[v] += (hi - lo + 1) * L[v];
			if (lo != hi) {
				F[2 * v + 1] = false;
				F[2 * v + 2] = false;
				L[2 * v + 1] += L[v];
				L[2 * v + 2] += L[v];
			}
			F[v] = true;
			L[v] = 0;
		}
	}

	void Update(int lo, int hi, int v, const int qlo, const int qhi, const int x) {
		Relax(lo, hi, v);
		if (qlo <= lo && hi <= qhi) {
			T[v] += (long long)(hi - lo + 1) * x;
			if (lo != hi) {
				F[2 * v + 1] = false;
				F[2 * v + 2] = false;
				L[2 * v + 1] += x;
				L[2 * v + 2] += x;
			}
			return;
		}
		if (qlo > hi || qhi < lo)
			return;
		int mid = (lo + hi) / 2;
		Update(lo, mid, 2 * v + 1, qlo, qhi, x);
		Update(mid + 1, hi, 2 * v + 2, qlo, qhi, x);
		T[v] = T[2 * v + 1] + T[2 * v + 2];
	}

	long long Query(int lo, int hi, int v, const int qlo, const int qhi) {
		Relax(lo, hi, v);
		if (qlo <= lo && hi <= qhi)
			return T[v];
		if (qlo > hi || qhi < lo)
			return 0;
		int mid = (lo + hi) / 2;
		long long sumLeft = Query(lo, mid, 2 * v + 1, qlo, qhi);
		long long sumRight = Query(mid + 1, hi, 2 * v + 2, qlo, qhi);
		return sumLeft + sumRight;
	}
};

int main() {
	scanf("%d %d", &N, &Q);
	for (int i = 0; i < N; ++i) {
		scanf("%d", &A[i]);
		R[i] = { 0, Q - 1 };
	}
	for (int i = 0; i < Q; ++i) {
		scanf("%d %d %d", &U[i][0], &U[i][1], &U[i][2]);
		--U[i][0];
		--U[i][1];
	}
	for (int i = 0; i < ceil(log2(Q)); i++) {
		for (int j = 0; j < Q; ++j)
			TS[j].clear();
		for (int j = 0; j < N; ++j) {
			auto [lo, hi] = R[j];
			if (lo < hi)
				TS[(lo + hi) / 2].push_back(j);
		}
		LazySegmentTree T(N);
		for (int j = 0; j < Q; ++j) {
			T.Update(0, N - 1, 0, U[j][0], U[j][1], U[j][2]);
			for (int k : TS[j]) {
				if (T.Query(0, N - 1, 0, k, k) >= A[k])
					R[k].second = j;
				else
					R[k].first = j + 1;
			}
		}
	}
	for (int i = 0; i < Q; ++i)
		TS[i].clear();
	for (int i = 0; i < N; ++i)
		TS[R[i].first].push_back(i);
	LazySegmentTree T(N);
	for (int i = 0; i < Q; ++i) {
		T.Update(0, N - 1, 0, U[i][0], U[i][1], U[i][2]);
		for (int j : TS[i]) {
			if (T.Query(0, N - 1, 0, j, j) >= A[j])
				B[j] = i + 1;
			else
				B[j] = -1;
		}
	}
	for (int i = 0; i < N; ++i)
		printf("%d ", B[i]);
}