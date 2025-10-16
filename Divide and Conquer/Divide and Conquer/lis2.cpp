#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

struct query {
	int X;
	int Y;
	int id;
	int index;
};

bool compareQueries(query A, query B) {
	return A.X < B.X;
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

void Update(vector<int>& T, vector<int>& A, vector<int>& P, vector<query>& I, int lo, int hi, int v, int i) {
	if (lo == hi) {
		T[v] = A[I[i].index];
		return;
	}
	int mid = (lo + hi) / 2;
	if (P[i] <= mid)
		Update(T, A, P, I, lo, mid, 2 * v + 1, i);
	else
		Update(T, A, P, I, mid + 1, hi, 2 * v + 2, i);
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

void AnswerQueries(vector<query>& I, vector<query>& Q, vector<int>& A) {
	sort(I.begin(), I.end(), compareQueries);
	sort(Q.begin(), Q.end(), compareQueries);
	vector<int> T(4 * I.size(), 0);
	set<pair<int, int>> S;
	vector<int> P(I.size());
	for (int i = 0; i < I.size(); ++i)
		S.insert({ I[i].Y, i });
	int i = 0;
	for (auto [_, index] : S)
		P[index] = i++;
	i = 0;
	for (int j = 0; j < Q.size(); ++j) {
		while (i < I.size() && I[i].X < Q[j].X)
			Update(T, A, P, I, 0, I.size() - 1, 0, i++);
		if (i > 0 && I[i - 1].X < Q[j].X) {
			auto it = S.lower_bound({ Q[j].Y, 0 });
			if (it->first < Q[j].Y) {
				A[Q[j].index] = max(A[Q[j].index], Query(T, 0, I.size() - 1, 0, 0, P[(it)->second]) + 1);
			}
			if (it != S.begin()) 
				A[Q[j].index] = max(A[Q[j].index], Query(T, 0, I.size() - 1, 0, 0, P[(--it)->second]) + 1);
		}
	}
}

void CDQ(int lo, int hi, vector<query>& Q, vector<int>& A) {
	if (lo == hi) {
		A[Q[lo].index] = 1;
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
	int N;
	scanf("%d", &N);
	vector<pair<int, int>> P(N);
	vector<query> Q(2 * N);
	vector<int> A(2 * N);
	for (int i = 0; i < N; ++i)
		scanf("%d %d", &P[i].first, &P[i].second);
	int j = 0;
	for (int i = 0; i < 2 * N; i += 2) {
		Q[i].id = 2; Q[i + 1].id = 1;
		Q[i].X = Q[i + 1].X = P[j].first;
		Q[i].Y = Q[i + 1].Y = P[j].second;
		Q[i].index = Q[i + 1].index = j++;
	}
	CDQ(0, 2 * N - 1, Q, A);
	printf("%d\n", *max_element(A.begin(), A.end()));
}