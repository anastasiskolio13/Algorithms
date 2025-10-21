#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

struct query {
	int L;
	int R;
	int index;
	int id;
};

bool CompareQueries(query A, query B) {
	return A.L < B.L;
}

vector<query> ExtractInsert(int lo, int hi, vector<query>& Q) {
	vector<query> A;
	for (int i = lo; i <= hi; ++i)
		if (Q[i].id == 1)
			A.push_back(Q[i]);
	return A;
}

vector<query> ExtractQuery(int lo, int hi, vector<query>& Q) {
	vector<query> A;
	for (int i = lo; i <= hi; ++i)
		if (Q[i].id == 2)
			A.push_back(Q[i]);
	return A;
}

void Update(vector<int>& T, vector<int>& P, int lo, int hi, int v, int i, int x) {
	if (lo == hi) {
		T[v] = x;
		return;
	}
	int mid = (lo + hi) / 2;
	if (P[i] <= mid)
		Update(T, P, lo, mid, 2 * v + 1, i, x);
	else
		Update(T, P, mid + 1, hi, 2 * v + 2, i, x);
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

void AnswerQueries(vector<query>& I, vector<query>& Q, vector<int>& A) {
	sort(I.begin(), I.end(), CompareQueries);
	sort(Q.begin(), Q.end(), CompareQueries);
	set<pair<int, int>> S;
	vector<int> P(I.size());
	vector<int> T(4 * I.size(), 0);
	for (int i = 0; i < I.size(); ++i)
		S.insert({ I[i].R, i });
	int i = 0;
	for (auto [_, index] : S)
		P[index] = i++;
	for (int i = 0; i < I.size(); ++i)
		Update(T, P, 0, I.size() - 1, 0, i, 1);
	i = 0;
	for (int j = 0; j < Q.size(); ++j) {
		while (i < I.size() && I[i].L < Q[j].L) 
			Update(T, P, 0, I.size() - 1, 0, i++, 0);
		auto it = S.upper_bound({ Q[j].R, -1 });
		A[Q[j].index] += it == S.begin() ? 0 : Query(T, 0, I.size() - 1, 0, 0, P[(--it)->second]);
	}
}

void CDQ(int lo, int hi, vector<query>& Q, vector<int>& A) {
	if (lo == hi) {
		A[lo] = 0;
		return;
	}
	int mid = (lo + hi) / 2;
	CDQ(lo, mid, Q, A);
	CDQ(mid + 1, hi, Q, A);
	vector<query> IL = ExtractInsert(lo, mid, Q);
	vector<query> QR = ExtractQuery(mid + 1, hi, Q);
	AnswerQueries(IL, QR, A);
}

int main() {
	int T;
	scanf("%d", &T);
	vector<query> Q(T);
	vector<int> A(T);
	for (int i = 0; i < T; ++i) {
		scanf("%d %d %d", &Q[i].id, &Q[i].L, &Q[i].R);
		Q[i].index = i;
	}
	CDQ(0, T - 1, Q, A);
	for (int i = 0; i < T; ++i)
		if (Q[i].id == 2)
			printf("%d\n", A[i]);
}