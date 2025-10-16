#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#define MAXN 100000
using namespace std;

struct query {
	int a;
	int b;
	int c;
};

bool CompareQueries(query A, query B) {
	return A.b > B.b;
}

vector<int> K(MAXN);
int N;

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
		while (i < I.size() && I[i].b > Q[j].b)
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
	scanf("%d", &N);
	vector<query> Q(2 * N);
	vector<int> A(2 * N);
	for (int i = 0; i < N; ++i) 
		scanf("%d", &K[i]);
	int j = 0;
	for (int i = 0; i < 2 * N; i += 2) {
		Q[i].a = 2;
		Q[i + 1].a = 1;
		Q[i].b = Q[i + 1].b = K[j];
		Q[i].c = Q[i + 1].c = i;
		++j;
	}
	CDQ(0, 2 * N - 1, Q, A);
	printf("%lld\n", accumulate(A.begin(), A.end(), 0));
}