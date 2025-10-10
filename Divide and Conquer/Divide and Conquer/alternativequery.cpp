#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXT 1000
using namespace std;

struct query {
	int a;
	int b;
	int c;
};

bool CompareQueries(query A, query B) {
	return A.b < B.b;
}

vector<query> ExtractInsert(int lo, int hi, vector<query>& Q) {
	vector<query> A;
	for (int i = lo; i <= hi; ++i)
		if (Q[i].a == 1)
			A.push_back(Q[i]);
	return A;
}

vector<query> ExtractQuery(int lo, int hi, vector<query>& Q) {
	vector<query> A;
	for (int i = lo; i <= hi; ++i)
		if (Q[i].a == 2)
			A.push_back(Q[i]);
	return A;
}

void AnswerQueries(vector<query>& I, vector<query>& Q, vector<int>& A) {
	sort(I.begin(), I.end(), CompareQueries);
	sort(Q.begin(), Q.end(), CompareQueries);
	int i = 0;
	for (int j = 0; j < Q.size(); ++j) {
		while (i < I.size() && I[i].b < Q[j].b)
			++i;
		A[Q[j].c] += i;
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
		scanf("%d %d", &Q[i].a, &Q[i].b);
		Q[i].c = i;
	}
	CDQ(0, T - 1, Q, A);
	for (int i = 0; i < T; ++i)
		if (Q[i].a == 2)
			printf("%d ", A[i]);
}