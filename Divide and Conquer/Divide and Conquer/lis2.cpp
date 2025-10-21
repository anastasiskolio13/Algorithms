#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

struct query {
	int T;
	int X;
	int Y;
	int I;
};

bool CompareQueries(query A, query B) {
	return A.X < B.X;
}

void Update(vector<int>& T, int lo, int hi, int v, int i, int x) {
	if (lo == hi) {
		T[v] = x;
		return;
	}
	int mid = (lo + hi) / 2;
	if (i <= mid)
		Update(T, lo, mid, 2 * v + 1, i, x);
	else
		Update(T, mid + 1, hi, 2 * v + 2, i, x);
	T[v] = max(T[2 * v + 1], T[2 * v + 2]);
}

int Query(vector<int>& T, int lo, int hi, int v, int qlo, int qhi) {
	if (qlo <= lo && hi <= qhi)
		return T[v];
	if (qlo > hi || qhi < lo)
		return 0;
	int mid = (lo + hi) / 2;
	int maxLeft = Query(T, lo, mid, 2 * v + 1, qlo, qhi);
	int maxRight = Query(T, mid + 1, hi, 2 * v + 2, qlo, qhi);
	return max(maxLeft, maxRight);
}

void AnswerQueries(vector<query>& I, vector<query>& A, vector<int>& B) {
	sort(I.begin(), I.end(), CompareQueries);
	sort(A.begin(), A.end(), CompareQueries);
	set<pair<int, int>> S;
	vector<int> P(I.size());
	vector<int> T(4 * I.size(), 0);
	for (int i = 0; i < I.size(); ++i)
		S.insert({ I[i].Y, i });
	int i = 0;
	for (auto [value, index] : S)
		P[index] = i++;
	i = 0;
	for (int j = 0; j < A.size(); ++j) {
		while (i < I.size() && I[i].X < A[j].X) {
			Update(T, 0, I.size() - 1, 0, P[i], B[I[i].I - 1]);
			++i;
		}
		auto iteratorOne = S.upper_bound({ A[j].Y, I.size()});
		if (iteratorOne != S.begin())
			B[A[j].I] = max(B[A[j].I], 1 + Query(T, 0, I.size() - 1, 0, 0, P[(--iteratorOne)->second]));
	}
}

void CDQ(int lo, int hi, vector<query>& Q, vector<int>& B) {
	if (lo == hi) {
		B[lo] = 1;
		return;
	}
	int mid = (lo + hi) / 2;
	CDQ(lo, mid, Q, B);
	CDQ(mid + 1, hi, Q, B);
	vector<query> I;
	for (int i = lo; i <= mid; ++i)
		if (Q[i].T == 1)
			I.push_back(Q[i]);
	vector<query> A;
	for (int i = mid + 1; i <= hi; ++i)
		if (Q[i].T == 2)
			A.push_back(Q[i]);
	AnswerQueries(I, A, B);
}

int main() {
	int N;
	scanf("%d", &N);
	vector<pair<int, int>> A(N);
	for (int i = 0; i < N; ++i) {
		scanf("%d %d", &A[i].first, &A[i].second);
	}
	vector<query> Q(2 * N);
	vector<int> B(2 * N);
	int j = 0;
	for (int i = 0; i < 2 * N; i += 2) {
		Q[i].T = 2; Q[i + 1].T = 1;
		Q[i].X = Q[i + 1].X = A[j].first;
		Q[i].Y = Q[i + 1].Y = A[j].second;
		Q[i].I = i; Q[i + 1].I = i + 1;
		++j;
	}
	CDQ(0, 2 * N - 1, Q, B);
	printf("%d\n", *max_element(B.begin(), B.begin() + 2 * N));
}