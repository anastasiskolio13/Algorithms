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
	int Z;
	int I;
};

bool CompareQueriesX(query A, query B) {
	return A.X > B.X;
}

bool CompareQueriesY(query A, query B) {
	return A.Y > B.Y;
}

void Update(vector<int>& T, vector<int>& P, int lo, int hi, int v, int i) {
	if (lo == hi) {
		T[v] = 1;
		return;
	}
	int mid = (lo + hi) / 2;
	if (P[i] <= mid)
		Update(T, P, lo, mid, 2 * v + 1, i);
	else
		Update(T, P, mid + 1, hi, 2 * v + 2, i);
	T[v] = T[2 * v + 1] + T[2 * v + 2];
}

int Query(vector<int>& T, int lo, int hi, int v, int qlo, int qhi) {
	if (qlo <= lo && hi <= qhi)
		return T[v];
	if (qlo > hi || qhi < lo)
		return 0;
	int mid = (lo + hi) / 2;
	int sumLeft = Query(T, lo, mid, 2 * v + 1, qlo, qhi);
	int sumRight = Query(T, mid + 1, hi, 2 * v + 2, qlo, qhi);
	return sumLeft + sumRight;
}

void AnswerQueries(vector<query>& I, vector<query>& A, vector<int>& B) {
	sort(I.begin(), I.end(), CompareQueriesY);
	sort(A.begin(), A.end(), CompareQueriesY);
	set<pair<int, int>> S;
	vector<int> P(I.size());
	vector<int> T(4 * I.size(), 0);
	for (int i = 0; i < I.size(); ++i)
		S.insert({ I[i].Z, i });
	int i = 0;
	for (auto [_, index] : S)
		P[index] = i++;
	i = 0;
	for (int j = 0; j < A.size(); ++j) {
		while (i < I.size() && I[i].Y > A[j].Y)
			Update(T, P, 0, I.size() - 1, 0, i++);
		auto iteratorOne = S.upper_bound({ A[j].Z, I.size() });
		if (iteratorOne != S.end())
			B[A[j].I] += Query(T, 0, I.size() - 1, 0, P[iteratorOne->second], I.size() - 1);
	}
}

void CDQ(int lo, int hi, vector<query>& Q, vector<int>& B) {
	if (lo == hi) {
		B[lo] = 0;
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
	// Από εδώ και κάτω στη συνάρτηση γίνεται η μαλακία.
	int i = I.size() - 1;
	while (i >= 0 && I[I.size() - 1].X == I[i].X)
		--i;
	int j = 0;
	while (j < A.size() && A[0].X == A[j].X)
		++j;
	vector<query> IL(I.begin(), I.begin() + i + 1);
	vector<query> AL(A.begin(), A.begin() + j);
	vector<query> AR(A.begin() + j, A.end());
	AnswerQueries(IL, AL, B);
	AnswerQueries(I, AR, B);
}

int main() {
	int N;
	scanf("%d", &N);
	vector<query> Q(2 * N);
	vector<int> B(2 * N);
	for (int i = 0; i < 2 * N; i += 2) {
		scanf("%d %d %d", &Q[i].X, &Q[i].Y, &Q[i].Z);
		Q[i + 1].T = 1; Q[i].T = 2;
		Q[i + 1].X = Q[i].X;
		Q[i + 1].Y = Q[i].Y;
		Q[i + 1].Z = Q[i].Z;
		Q[i + 1].I = i + 1; Q[i].I = i;
	}
	sort(Q.begin(), Q.end(), CompareQueriesX);
	CDQ(0, 2 * N - 1, Q, B);
	for (int i = 0; i < 2 * N; i += 2)
		printf("%d\n", B[i]);
}
