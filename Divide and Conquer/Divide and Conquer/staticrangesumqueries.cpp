#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAXN 200000
#define MAXT 200000
using namespace std;

struct query {
	int L;
	int R;
	int idx;
};

vector<int> A(MAXN);
vector<long long> B(MAXT);
vector<long long> SL(MAXN);
vector<long long> SR(MAXN);
int N;
int T;

void DivideAndConquer(int lo, int hi, vector<query> Q) {
	if (lo == hi) {
		for (int i = 0; i < Q.size(); ++i)
			B[Q[i].idx] = A[lo];
		return;
	}
	int mid = (lo + hi) / 2;
	long long sumLeft = 0;
	for (int i = mid; i >= lo; --i) {
		sumLeft += A[i];
		SL[i] = sumLeft;
	}
	long long sumRight = 0;
	for (int i = mid + 1; i <= hi; ++i) {
		sumRight += A[i];
		SR[i] = sumRight;
	}
	vector<query> QL;
	vector<query> QR;
	for (int i = 0; i < Q.size(); ++i) {
		if (Q[i].L <= mid && mid < Q[i].R)
			B[Q[i].idx] = SL[Q[i].L] + SR[Q[i].R];
		else if (Q[i].R <= mid)
			QL.push_back(Q[i]);
		else
			QR.push_back(Q[i]);
	}
	DivideAndConquer(lo, mid, QL);
	DivideAndConquer(mid + 1, hi, QR);
}

int main() {
	scanf("%d %d", &N, &T);
	for (int i = 0; i < N; ++i)
		scanf("%d", &A[i]);
	vector<query> Q(T);
	for (int i = 0; i < T; ++i) {
		scanf("%d %d", &Q[i].L, &Q[i].R);
		--Q[i].L; 
		--Q[i].R;
		Q[i].idx = i;
	}
	DivideAndConquer(0, N - 1, Q);
	for (int i = 0; i < T; ++i)
		printf("%lld\n", B[i]);
}