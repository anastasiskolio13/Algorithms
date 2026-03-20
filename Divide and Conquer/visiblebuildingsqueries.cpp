#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#define MAXN 100000
#define MAXT 200000
using namespace std;

struct query {
	int L;
	int R;
	int idx;
};

vector<int> H(MAXN);
vector<int> B(MAXT);
vector<int> VL(MAXN);
vector<int> VR(MAXN);
vector<int> maxLeftHeightUntil(MAXN);
vector<int> maxRightHeightUntil(MAXN);
int N;
int T;

int BinarySearch(int lo, int hi, int i) {
	while (lo < hi) {
		int mid = (lo + hi) / 2;
		if (maxRightHeightUntil[mid] > maxLeftHeightUntil[i])
			hi = mid;
		else
			lo = mid + 1;
	}
	return maxRightHeightUntil[lo] > maxLeftHeightUntil[i] ? lo : -1;
}

void DivideAndConquer(int lo, int hi, vector<query> Q) {
	if (lo == hi) {
		for (int i = 0; i < Q.size(); ++i)
			B[Q[i].idx] = 1;
		return;
	}
	int mid = (lo + hi) / 2;
	stack<int> S;
	maxLeftHeightUntil[mid + 1] = 0;
	for (int i = mid; i >= lo; --i) {
		while (!S.empty() && H[i] >= H[S.top()])
			S.pop();
		S.push(i);
		VL[i] = S.size();
		maxLeftHeightUntil[i] = max(maxLeftHeightUntil[i + 1], H[i]);
	}
	int totalVisible = 0;
	maxRightHeightUntil[mid] = 0;
	VR[mid] = 0;
	for (int i = mid + 1; i <= hi; ++i) {
		if (H[i] > maxRightHeightUntil[i - 1]) {
			VR[i] = ++totalVisible;
			maxRightHeightUntil[i] = H[i];
		}
		else {
			VR[i] = totalVisible;
			maxRightHeightUntil[i] = maxRightHeightUntil[i - 1];
		}
	}
	vector<query> QL;
	vector<query> QR;
	for (int i = 0; i < Q.size(); ++i) {
		if (Q[i].L <= mid && mid < Q[i].R) {
			int p = BinarySearch(mid + 1, Q[i].R, Q[i].L);
			B[Q[i].idx] = VL[Q[i].L] + (p != -1 ? VR[Q[i].R] - VR[p - 1] : 0);
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
	scanf("%d %d", &N, &T);
	for (int i = 0; i < N; ++i)
		scanf("%d", &H[i]);
	vector<query> Q(T);
	for (int i = 0; i < T; ++i) {
		scanf("%d %d", &Q[i].L, &Q[i].R);
		--Q[i].L;
		--Q[i].R;
		Q[i].idx = i;
	}
	DivideAndConquer(0, N - 1, Q);
	for (int i = 0; i < T; ++i)
		printf("%d\n", B[i]);
}
