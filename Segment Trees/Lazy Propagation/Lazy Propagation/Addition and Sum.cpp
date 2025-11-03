#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;

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
	int N, M;
	scanf("%d %d", &N, &M);
	LazySegmentTree T(N);
	while (M--) {
		int a, b, c, d;
		scanf("%d %d %d", &a, &b, &c);
		if (a == 1) {
			scanf("%d", &d);
			T.Update(0, N - 1, 0, b, --c, d);
		}
		else {
			printf("%lld\n", T.Query(0, N - 1, 0, b, --c));
		}
	}
}