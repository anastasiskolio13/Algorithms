#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <set>
using namespace std;

struct query {
	int X;
	int Y;
	int Z;
	int index;
	int id;
};

bool CompareQuries(query A, query B) {
	return A.Y < B.Y;
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

void AnswerQueries(vector<query>& I, vector<query>& Q, vector<int>& A) {
	sort(I.begin(), I.end(), CompareQuries);
	sort(Q.begin(), Q.end(), CompareQuries);

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

vector<query> ReduceItToInsertQueryProblem(vector<tuple<int, int, int>>& P) {
	vector<query> A(2 * P.size());
	int j = 0;
	for (int i = 0; i < 2 * P.size(); i += 2) {
		A[i].X = A[i + 1].X = get<0>(P[j]);
		A[i].Y = A[i + 1].Y = get<1>(P[j]);
		A[i].Z = A[i + 1].Z = get<2>(P[j]);
		A[i].index = A[i + 1].index = j;
		A[i].id = 2; A[i + 1].id = 1;
		++j;
	}
	return A;

}

int main() {
	int N;
	vector<tuple<int, int, int>> P(N);
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		int X, Y, Z;
		scanf("%d %d %d", &X, &Y, &Z);
		P[i] = { X, Y, Z };
	}
	// Sort the points in decreasing order of X.
	sort(P.begin(), P.end(), greater<tuple<int, int, int>>());
	// Reduce the problem to an insert - query problem.
	vector<query> Q = ReduceItToInsertQueryProblem(P);
	// Store the answers of the queries.
	vector<int> A(2 * N);
	// CDQ D&C.
	CDQ(0, 2 * N - 1, Q, A);
	// Print the answers.
	for (int i = 0; i < 2 * N; i += 2)
			printf("%d\n", A[i]);
}