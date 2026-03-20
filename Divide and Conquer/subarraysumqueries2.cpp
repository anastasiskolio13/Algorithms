#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 200000
#define MAXT 200000
using namespace std;

struct query {
	int L;
	int R;
	int idx;
};

vector<int> X(MAXN);
vector<long long> B(MAXT);
vector<long long> maximumSumLeft(MAXN);
vector<long long> maximumSumRight(MAXN);
vector<long long> dpLeft(MAXN);
vector<long long> dpRight(MAXN);
vector<long long> maximumLeftSubarraySumUntil(MAXN);
vector<long long> maximumRightSubarraySumUntil(MAXN);
int N;
int T;

void DivideAndConquer(int lo, int hi, vector<query> Q) {
	if (lo == hi) {
		for (int i = 0; i < Q.size(); ++i)
			B[Q[i].idx] = max(X[lo], 0);
		return;
	}
	int mid = (lo + hi) / 2;
	long long sumLeft = maximumLeftSubarraySumUntil[mid] = dpLeft[mid] = maximumSumLeft[mid] = X[mid];
	for (int i = mid - 1; i >= lo; --i) {
		sumLeft += X[i];
		maximumSumLeft[i] = max(maximumSumLeft[i + 1], sumLeft);
		dpLeft[i] = max(dpLeft[i + 1], 0LL) + X[i];
		maximumLeftSubarraySumUntil[i] = max(maximumLeftSubarraySumUntil[i + 1], dpLeft[i]);
	}
	long long sumRight = maximumRightSubarraySumUntil[mid + 1] = dpRight[mid + 1] = maximumSumRight[mid + 1] = X[mid + 1];
	for (int i = mid + 2; i <= hi; ++i) {
		sumRight += X[i];
		maximumSumRight[i] = max(maximumSumRight[i - 1], sumRight);
		dpRight[i] = max(dpRight[i - 1], 0LL) + X[i];
		maximumRightSubarraySumUntil[i] = max(maximumRightSubarraySumUntil[i - 1], dpRight[i]);
	}
	vector<query> QL;
	vector<query> QR;
	for (auto [L, R, idx] : Q) {
		if (L <= mid && mid < R) 
			B[idx] = max({ maximumLeftSubarraySumUntil[L], maximumSumLeft[L] + maximumSumRight[R], maximumRightSubarraySumUntil[R], 0LL });
		else if (R <= mid) 
			QL.push_back({ L, R, idx });
		
		else 
			QR.push_back({ L, R, idx });
	}
	DivideAndConquer(lo, mid, QL);
	DivideAndConquer(mid + 1, hi, QR);
}

int main() {
	scanf("%d %d", &N, &T);
	for (int i = 0; i < N; ++i)
		scanf("%d", &X[i]);
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